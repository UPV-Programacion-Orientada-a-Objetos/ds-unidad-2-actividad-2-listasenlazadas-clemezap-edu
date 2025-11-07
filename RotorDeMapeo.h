/**
 * @file RotorDeMapeo.h
 * @brief Implementación de lista circular doblemente enlazada para el rotor de mapeo
 * @author Sistema de Decodificación PRT-7
 * @date 2025
 */

#ifndef ROTOR_DE_MAPEO_H
#define ROTOR_DE_MAPEO_H

/**
 * @struct NodoRotor
 * @brief Nodo de la lista circular doblemente enlazada del rotor
 */
struct NodoRotor {
    char dato;            ///< Carácter almacenado en el nodo
    NodoRotor* siguiente; ///< Puntero al siguiente nodo
    NodoRotor* previo;    ///< Puntero al nodo previo
    
    /**
     * @brief Constructor del nodo
     * @param c Carácter a almacenar
     */
    NodoRotor(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class RotorDeMapeo
 * @brief Lista circular doblemente enlazada que actúa como disco de cifrado
 * 
 * Implementa una rueda de César que puede rotar para cambiar el mapeo
 * de caracteres dinámicamente.
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza; ///< Puntero a la posición cero actual del rotor
    
public:
    /**
     * @brief Constructor que inicializa el rotor con el alfabeto A-Z
     */
    RotorDeMapeo();
    
    /**
     * @brief Destructor que libera la memoria de todos los nodos
     */
    ~RotorDeMapeo();
    
    /**
     * @brief Rota el rotor N posiciones
     * @param N Número de posiciones a rotar (positivo o negativo)
     */
    void rotar(int N);
    
    /**
     * @brief Obtiene el carácter mapeado según la rotación actual
     * @param in Carácter de entrada a mapear
     * @return Carácter mapeado según la posición actual del rotor
     */
    char getMapeo(char in);
};

#endif // ROTOR_DE_MAPEO_H