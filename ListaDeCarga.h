/**
 * @file ListaDeCarga.h
 * @brief Implementación de lista doblemente enlazada para almacenar los datos decodificados
 * @author Sistema de Decodificación PRT-7
 * @date 2025
 */

#ifndef LISTA_DE_CARGA_H
#define LISTA_DE_CARGA_H

/**
 * @struct NodoCarga
 * @brief Nodo de la lista doblemente enlazada de carga
 */
struct NodoCarga {
    char dato;            ///< Carácter decodificado almacenado
    NodoCarga* siguiente; ///< Puntero al siguiente nodo
    NodoCarga* previo;    ///< Puntero al nodo previo
    
    /**
     * @brief Constructor del nodo
     * @param c Carácter a almacenar
     */
    NodoCarga(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class ListaDeCarga
 * @brief Lista doblemente enlazada para almacenar caracteres decodificados en orden
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza; ///< Puntero al primer nodo de la lista
    NodoCarga* cola;   ///< Puntero al último nodo de la lista
    
public:
    /**
     * @brief Constructor que inicializa una lista vacía
     */
    ListaDeCarga();
    
    /**
     * @brief Destructor que libera la memoria de todos los nodos
     */
    ~ListaDeCarga();
    
    /**
     * @brief Inserta un carácter al final de la lista
     * @param dato Carácter a insertar
     */
    void insertarAlFinal(char dato);
    
    /**
     * @brief Imprime el mensaje completo almacenado en la lista
     */
    void imprimirMensaje();
    
    /**
     * @brief Obtiene el mensaje actual como cadena de caracteres
     * @return Puntero a cadena con el mensaje (debe ser liberado por el llamador)
     */
    char* obtenerMensaje();
};

#endif // LISTA_DE_CARGA_H