/**
 * @file TramaBase.h
 * @brief Clase base abstracta para todas las tramas del protocolo PRT-7
 * @author Sistema de Decodificación PRT-7
 * @date 2025
 */

#ifndef TRAMA_BASE_H
#define TRAMA_BASE_H

// Forward declarations
class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Clase base abstracta que define la interfaz para todas las tramas
 * 
 * Esta clase proporciona una interfaz común para procesar diferentes tipos
 * de tramas recibidas desde el puerto serial.
 */
class TramaBase {
public:
    /**
     * @brief Método virtual puro para procesar la trama
     * @param carga Puntero a la lista de carga donde se almacenan los datos decodificados
     * @param rotor Puntero al rotor de mapeo usado para la decodificación
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
    
    /**
     * @brief Destructor virtual para permitir polimorfismo correcto
     */
    virtual ~TramaBase() {}
};

#endif // TRAMA_BASE_H