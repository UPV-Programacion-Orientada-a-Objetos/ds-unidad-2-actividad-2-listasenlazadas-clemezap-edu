/**
 * @file main.cpp
 * @brief Programa principal del decodificador PRT-7
 * @author Sistema de Decodificación PRT-7
 * @date 2025
 * 
 * Este programa lee tramas del puerto serial y decodifica mensajes ocultos
 * usando estructuras de datos de listas enlazadas.
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "TramaBase.h"
#include "TramaLoad.h"
#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <unistd.h>
    #include <termios.h>
#endif

/**
 * @brief Abre el puerto serial según el sistema operativo
 * @param puerto Nombre del puerto (ej. "COM3" o "/dev/ttyUSB0")
 * @return Handle/descriptor del puerto o valor inválido si falla
 */
#ifdef _WIN32
HANDLE abrirPuertoSerial(const char* puerto) {
    HANDLE hSerial = CreateFileA(puerto, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        return INVALID_HANDLE_VALUE;
    }
    
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        return INVALID_HANDLE_VALUE;
    }
    
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        CloseHandle(hSerial);
        return INVALID_HANDLE_VALUE;
    }
    
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    
    SetCommTimeouts(hSerial, &timeouts);
    
    return hSerial;
}
#else
int abrirPuertoSerial(const char* puerto) {
    int fd = open(puerto, O_RDONLY | O_NOCTTY);
    
    if (fd == -1) {
        return -1;
    }
    
    struct termios options;
    tcgetattr(fd, &options);
    
    cfsetispeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    
    tcsetattr(fd, TCSANOW, &options);
    
    return fd;
}
#endif

/**
 * @brief Lee una línea del puerto serial
 * @param handle Handle/descriptor del puerto
 * @param buffer Buffer donde se almacenará la línea
 * @param maxLen Tamaño máximo del buffer
 * @return true si se leyó una línea completa, false si no
 */
#ifdef _WIN32
bool leerLineaSerial(HANDLE hSerial, char* buffer, int maxLen) {
    static char bufferInterno[256];
    static int posBuffer = 0;
    static int bytesDisponibles = 0;
    
    while (true) {
        if (posBuffer < bytesDisponibles) {
            for (int i = posBuffer; i < bytesDisponibles; i++) {
                if (bufferInterno[i] == '\n') {
                    int longitud = i - posBuffer;
                    if (longitud > 0 && bufferInterno[i-1] == '\r') longitud--;
                    
                    if (longitud > 0 && longitud < maxLen) {
                        for (int j = 0; j < longitud; j++) {
                            buffer[j] = bufferInterno[posBuffer + j];
                        }
                        buffer[longitud] = '\0';
                        posBuffer = i + 1;
                        return true;
                    }
                    posBuffer = i + 1;
                }
            }
        }
        
        posBuffer = 0;
        DWORD bytesLeidos;
        if (!ReadFile(hSerial, bufferInterno, sizeof(bufferInterno) - 1, &bytesLeidos, NULL)) {
            return false;
        }
        
        if (bytesLeidos == 0) {
            return false;
        }
        
        bytesDisponibles = bytesLeidos;
        bufferInterno[bytesLeidos] = '\0';
    }
}
#else
bool leerLineaSerial(int fd, char* buffer, int maxLen) {
    static char bufferInterno[256];
    static int posBuffer = 0;
    static int bytesDisponibles = 0;
    
    while (true) {
        if (posBuffer < bytesDisponibles) {
            for (int i = posBuffer; i < bytesDisponibles; i++) {
                if (bufferInterno[i] == '\n') {
                    int longitud = i - posBuffer;
                    if (longitud > 0 && bufferInterno[i-1] == '\r') longitud--;
                    
                    if (longitud > 0 && longitud < maxLen) {
                        for (int j = 0; j < longitud; j++) {
                            buffer[j] = bufferInterno[posBuffer + j];
                        }
                        buffer[longitud] = '\0';
                        posBuffer = i + 1;
                        return true;
                    }
                    posBuffer = i + 1;
                }
            }
        }
        
        posBuffer = 0;
        int bytesLeidos = read(fd, bufferInterno, sizeof(bufferInterno) - 1);
        
        if (bytesLeidos <= 0) {
            return false;
        }
        
        bytesDisponibles = bytesLeidos;
        bufferInterno[bytesLeidos] = '\0';
    }
}
#endif

/**
 * @brief Parsea una línea y crea la trama correspondiente
 * @param linea Línea leída del puerto serial
 * @return Puntero a la trama creada o nullptr si hay error
 */
TramaBase* parsearTrama(char* linea) {
    if (!linea || linea[0] == '\0') return nullptr;
    
    // Parsear tipo de trama
    char tipo = linea[0];
    
    if (linea[1] != ',') return nullptr;
    
    if (tipo == 'L') {
        // Trama LOAD: L,X
        char caracter = linea[2];
        if (caracter == '\0') return nullptr;
        
        // Manejar caso especial de "Space"
        if (linea[2] == 'S' && linea[3] == 'p' && linea[4] == 'a' && 
            linea[5] == 'c' && linea[6] == 'e') {
            caracter = ' ';
        }
        
        return new TramaLoad(caracter);
    } 
    else if (tipo == 'M') {
        // Trama MAP: M,N
        int rotacion = atoi(&linea[2]);
        return new TramaMap(rotacion);
    }
    
    return nullptr;
}

/**
 * @brief Función principal del programa
 */
int main() {
    std::cout << "Iniciando Decodificador PRT-7. Conectando a puerto COM..." << std::endl;
    
    // Inicializar estructuras
    ListaDeCarga miListaDeCarga;
    RotorDeMapeo miRotorDeMapeo;
    
    // Intentar abrir puerto serial
    const char* nombrePuerto;
    
    #ifdef _WIN32
        nombrePuerto = "\\\\.\\COM3"; // Cambiar según necesidad
        HANDLE hSerial = abrirPuertoSerial(nombrePuerto);
        
        if (hSerial == INVALID_HANDLE_VALUE) {
            std::cout << "No se pudo abrir el puerto serial. Usando modo de prueba con datos simulados." << std::endl;
            std::cout << "Conexion establecida. Esperando tramas..." << std::endl << std::endl;
            
            // Datos de prueba del README
            const char* tramasPrueba[] = {
                "L,H", "L,O", "L,L", "M,2", "L,A", "L,Space", 
                "L,W", "M,-2", "L,O", "L,R", "L,L", "L,D", nullptr
            };
            
            for (int i = 0; tramasPrueba[i] != nullptr; i++) {
                char buffer[256];
                strcpy(buffer, tramasPrueba[i]);
                
                TramaBase* trama = parsearTrama(buffer);
                if (trama) {
                    trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
                    delete trama;
                }
            }
        } else {
            std::cout << "Conexion establecida. Esperando tramas..." << std::endl << std::endl;
            
            char buffer[256];
            while (leerLineaSerial(hSerial, buffer, sizeof(buffer))) {
                TramaBase* trama = parsearTrama(buffer);
                if (trama) {
                    trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
                    delete trama;
                }
            }
            
            CloseHandle(hSerial);
        }
    #else
        nombrePuerto = "/dev/ttyUSB0"; // Cambiar según necesidad
        int fd = abrirPuertoSerial(nombrePuerto);
        
        if (fd == -1) {
            std::cout << "No se pudo abrir el puerto serial. Usando modo de prueba con datos simulados." << std::endl;
            std::cout << "Conexion establecida. Esperando tramas..." << std::endl << std::endl;
            
            // Datos de prueba del README
            const char* tramasPrueba[] = {
                "L,H", "L,O", "L,L", "M,2", "L,A", "L,Space", 
                "L,W", "M,-2", "L,O", "L,R", "L,L", "L,D", nullptr
            };
            
            for (int i = 0; tramasPrueba[i] != nullptr; i++) {
                char buffer[256];
                strcpy(buffer, tramasPrueba[i]);
                
                TramaBase* trama = parsearTrama(buffer);
                if (trama) {
                    trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
                    delete trama;
                }
            }
        } else {
            std::cout << "Conexion establecida. Esperando tramas..." << std::endl << std::endl;
            
            char buffer[256];
            while (leerLineaSerial(fd, buffer, sizeof(buffer))) {
                TramaBase* trama = parsearTrama(buffer);
                if (trama) {
                    trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
                    delete trama;
                }
            }
            
            close(fd);
        }
    #endif
    
    // Mostrar resultado final
    std::cout << std::endl << "---" << std::endl;
    std::cout << "Flujo de datos terminado." << std::endl;
    std::cout << "MENSAJE OCULTO ENSAMBLADO:" << std::endl;
    miListaDeCarga.imprimirMensaje();
    std::cout << "---" << std::endl;
    std::cout << "Liberando memoria... Sistema apagado." << std::endl;
    
    return 0;
}