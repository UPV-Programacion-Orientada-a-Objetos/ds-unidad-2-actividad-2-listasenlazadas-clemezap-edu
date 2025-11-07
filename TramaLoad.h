/**
 * @file TramaLoad.h
 * @brief Clase para tramas de tipo LOAD que contienen fragmentos de datos
 * @author Sistema de Decodificación PRT-7
 * @date 2025
 */

#ifndef TRAMA_LOAD_H
#define TRAMA_LOAD_H

#include "TramaBase.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @class TramaLoad
 * @brief Representa una trama LOAD que contiene un carácter a decodificar
 * 
 * Las tramas LOAD contienen un fragmento de dato (un carácter) que debe
 * ser decodificado usando el estado actual del rotor de mapeo.
 */
class TramaLoad : public TramaBase {
private:
    char caracter; ///< Carácter contenido en la trama
    
public:
    /**
     * @brief Constructor de la trama LOAD
     * @param c Carácter a almacenar en la trama
     */
    TramaLoad(char c);
    
    /**
     * @brief Procesa la trama LOAD decodificando el carácter
     * @param carga Lista donde se insertará el carácter decodificado
     * @param rotor Rotor usado para mapear el carácter
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_LOAD_H