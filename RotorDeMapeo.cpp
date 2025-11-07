/**
 * @file RotorDeMapeo.cpp
 * @brief Implementación de la clase RotorDeMapeo
 * @author Sistema de Decodificación PRT-7
 * @date 2025
 */

#include "RotorDeMapeo.h"

RotorDeMapeo::RotorDeMapeo() {
    // Crear el primer nodo con 'A'
    cabeza = new NodoRotor('A');
    NodoRotor* actual = cabeza;
    
    // Crear nodos para B-Z
    for (char c = 'B'; c <= 'Z'; c++) {
        NodoRotor* nuevo = new NodoRotor(c);
        actual->siguiente = nuevo;
        nuevo->previo = actual;
        actual = nuevo;
    }
    
    // Crear nodo para espacio
    NodoRotor* espacio = new NodoRotor(' ');
    actual->siguiente = espacio;
    espacio->previo = actual;
    actual = espacio;
    
    // Cerrar el círculo
    actual->siguiente = cabeza;
    cabeza->previo = actual;
}

RotorDeMapeo::~RotorDeMapeo() {
    if (!cabeza) return;
    
    NodoRotor* actual = cabeza->siguiente;
    while (actual != cabeza) {
        NodoRotor* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    delete cabeza;
}

void RotorDeMapeo::rotar(int N) {
    if (!cabeza || N == 0) return;
    
    if (N > 0) {
        // Rotar a la derecha
        for (int i = 0; i < N; i++) {
            cabeza = cabeza->siguiente;
        }
    } else {
        // Rotar a la izquierda
        for (int i = 0; i < -N; i++) {
            cabeza = cabeza->previo;
        }
    }
}

char RotorDeMapeo::getMapeo(char in) {
    // Buscar el carácter en el rotor
    NodoRotor* actual = cabeza;
    int posicion = 0;
    
    do {
        if (actual->dato == in) {
            // Encontrado, ahora avanzar desde cabeza la misma cantidad
            NodoRotor* resultado = cabeza;
            for (int i = 0; i < posicion; i++) {
                resultado = resultado->siguiente;
            }
            return resultado->dato;
        }
        posicion++;
        actual = actual->siguiente;
    } while (actual != cabeza);
    
    // Si no se encuentra, retornar el mismo carácter
    return in;
}