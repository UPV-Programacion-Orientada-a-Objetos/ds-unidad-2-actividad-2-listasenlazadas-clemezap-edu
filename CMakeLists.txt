cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(DecodificadorPRT7 VERSION 1.0)

# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Archivos fuente
set(SOURCES
    main.cpp
    RotorDeMapeo.cpp
    ListaDeCarga.cpp
    TramaLoad.cpp
    TramaMap.cpp
)

# Archivos de encabezado
set(HEADERS
    TramaBase.h
    RotorDeMapeo.h
    ListaDeCarga.h
    TramaLoad.h
    TramaMap.h
)

# Crear el ejecutable
add_executable(DecodificadorPRT7 ${SOURCES} ${HEADERS})

# Configuración para Windows
if(WIN32)
    # No se necesitan bibliotecas adicionales para Windows
endif()

# Configuración para Linux/Unix
if(UNIX)
    # No se necesitan bibliotecas adicionales para Linux
endif()

# Configuración de instalación
install(TARGETS DecodificadorPRT7 DESTINATION bin)

# Generar documentación con Doxygen (opcional)
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generando documentación con Doxygen"
        VERBATIM)
endif()