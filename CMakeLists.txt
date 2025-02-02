# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(DataStructures)

# Configuración de las rutas de inclusión
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

# Directorio de código fuente
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Directorio de salida para los ejecutables
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

# Obtener todos los archivos .cpp en el directorio src y sus subdirectorios
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")

# Crear un ejecutable para cada archivo .cpp
foreach(SRC_FILE ${SRC_FILES})
    # Obtener el nombre base del archivo sin la extensión
    get_filename_component(EXECUTABLE_NAME ${SRC_FILE} NAME_WE)

    # Crear el ejecutable
    add_executable(${EXECUTABLE_NAME} ${SRC_FILE})

    # Especificar la ubicación del ejecutable
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    )
endforeach()

# Mensaje informativo
message(STATUS "Ejecutables serán generados en: ${BIN_DIR}")