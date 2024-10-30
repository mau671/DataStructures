cmake_minimum_required(VERSION 3.29)
project(Diccionarios)

cmake_minimum_required(VERSION 3.29)
project(Diccionarios)

set(CMAKE_CXX_STANDARD 14)

# Incluir directorios de encabezados
include_directories(include)

# Agregar archivos de encabezado y fuentes organizados en carpetas
add_executable(Diccionarios
        # Archivos de implementación en `src`
        src/Diccionarios.cpp

        # Archivos de encabezado de estructuras abstractas
        include/Estructuras/Abstractas/Dictionary.h
        include/Estructuras/Abstractas/List.h

        # Archivos de encabezado de estructuras concretas: Diccionarios
        include/Estructuras/Concretas/Diccionarios/AVLDictionary.h
        include/Estructuras/Concretas/Diccionarios/BSTDictionary.h
        include/Estructuras/Concretas/Diccionarios/HashTable.h
        include/Estructuras/Concretas/Diccionarios/UnsortedArrayDictionary.h

        # Archivos de encabezado de estructuras concretas: Listas
        include/Estructuras/Concretas/Listas/ArrayList.h
        include/Estructuras/Concretas/Listas/DLinkedList.h

        # Archivos de encabezado de estructuras concretas: Árboles
        include/Estructuras/Concretas/Arboles/AVLTree.h
        include/Estructuras/Concretas/Arboles/BSTree.h
        include/Estructuras/Concretas/Arboles/SplayTree.h

        # Archivos de nodos
        include/Estructuras/Nodos/BSTNode.h
        include/Estructuras/Nodos/DNode.h
        include/Estructuras/Nodos/SNode.h

        # Archivos adicionales
        include/Estructuras/Concretas/KVPair.h
)

# Incluir directorios con rutas cortas
target_include_directories(Diccionarios PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)