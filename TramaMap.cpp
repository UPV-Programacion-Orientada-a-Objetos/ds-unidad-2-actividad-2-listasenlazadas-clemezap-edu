/**
 * @file TramaMap.cpp
 * @brief Implementación de la clase TramaMap
 * @author Sistema de Decodificación PRT-7
 * @date 2025
 */

#include "TramaMap.h"
#include <iostream>

TramaMap::TramaMap(int n) : rotacion(n) {}

void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    rotor->rotar(rotacion);
    
    // Mostrar progreso
    std::cout << std::endl << "Trama recibida: [M," << rotacion << "] -> Procesando... -> ROTANDO ROTOR ";
    if (rotacion >= 0) {
        std::cout << "+" << rotacion;
    } else {
        std::cout << rotacion;
    }
    std::cout << "." << std::endl << std::endl;
}