/**
 * @file TramaMap.h
 * @brief Clase para tramas de tipo MAP que modifican la rotación del rotor
 * @author Sistema de Decodificación PRT-7
 * @date 2025
 */

#ifndef TRAMA_MAP_H
#define TRAMA_MAP_H

#include "TramaBase.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @class TramaMap
 * @brief Representa una trama MAP que rota el disco de cifrado
 * 
 * Las tramas MAP contienen un valor entero que indica cuántas posiciones
 * debe rotar el rotor de mapeo (positivo o negativo).
 */
class TramaMap : public TramaBase {
private:
    int rotacion; ///< Número de posiciones a rotar
    
public:
    /**
     * @brief Constructor de la trama MAP
     * @param n Número de posiciones a rotar
     */
    TramaMap(int n);
    
    /**
     * @brief Procesa la trama MAP rotando el rotor
     * @param carga Lista de carga (no se usa en MAP)
     * @param rotor Rotor a rotar
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_MAP_H