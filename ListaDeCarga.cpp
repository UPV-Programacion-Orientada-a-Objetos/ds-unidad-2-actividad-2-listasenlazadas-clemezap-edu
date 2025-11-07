/**
 * @file ListaDeCarga.cpp
 * @brief Implementación de la clase ListaDeCarga
 * @author Sistema de Decodificación PRT-7
 * @date 2025
 */

#include "ListaDeCarga.h"
#include <iostream>

ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr) {}

ListaDeCarga::~ListaDeCarga() {
    NodoCarga* actual = cabeza;
    while (actual) {
        NodoCarga* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevo = new NodoCarga(dato);
    
    if (!cabeza) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->previo = cola;
        cola = nuevo;
    }
}

void ListaDeCarga::imprimirMensaje() {
    NodoCarga* actual = cabeza;
    while (actual) {
        std::cout << actual->dato;
        actual = actual->siguiente;
    }
    std::cout << std::endl;
}

char* ListaDeCarga::obtenerMensaje() {
    // Contar caracteres
    int longitud = 0;
    NodoCarga* actual = cabeza;
    while (actual) {
        longitud++;
        actual = actual->siguiente;
    }
    
    // Crear cadena
    char* mensaje = new char[longitud + 1];
    actual = cabeza;
    int i = 0;
    while (actual) {
        mensaje[i++] = actual->dato;
        actual = actual->siguiente;
    }
    mensaje[i] = '\0';
    
    return mensaje;
}