/**
 * @file TramaLoad.cpp
 * @brief Implementación de la clase TramaLoad
 * @author Sistema de Decodificación PRT-7
 * @date 2025
 */

#include "TramaLoad.h"
#include <iostream>

TramaLoad::TramaLoad(char c) : caracter(c) {}

void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    char decodificado = rotor->getMapeo(caracter);
    carga->insertarAlFinal(decodificado);
    
    // Mostrar progreso
    std::cout << "Trama recibida: [L," << caracter << "] -> Procesando... -> Fragmento '" 
              << caracter << "' decodificado como '" << decodificado << "'. Mensaje: [";
    
    char* mensaje = carga->obtenerMensaje();
    for (int i = 0; mensaje[i] != '\0'; i++) {
        std::cout << mensaje[i];
        if (mensaje[i + 1] != '\0') std::cout << "][";
    }
    std::cout << "]" << std::endl;
    delete[] mensaje;
}