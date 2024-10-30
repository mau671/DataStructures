cmake_minimum_required(VERSION 3.29)
project(DataStructures)

cmake_minimum_required(VERSION 3.29)
project(DataStructures)

set(CMAKE_CXX_STANDARD 14)

# Incluir directorios de encabezados
include_directories(include)

# Agregar archivos de encabezado y fuentes organizados en carpetas
add_executable(DataStructures
        # Archivos de implementación en `src`
        src/Diccionarios.cpp

        # Archivos de encabezado de estructuras abstractas
        include/Structures/Abstract/Dictionary.h
        include/Structures/Abstract/List.h

        # Archivos de encabezado de estructuras concretas: Diccionarios
        include/Structures/Implementations/Dictionaries/AVLDictionary.h
        include/Structures/Implementations/Dictionaries/BSTDictionary.h
        include/Structures/Implementations/Dictionaries/HashTable.h
        include/Structures/Implementations/Dictionaries/UnsortedArrayDictionary.h

        # Archivos de encabezado de estructuras concretas: Listas
        include/Structures/Implementations/Lists/ArrayList.h
        include/Structures/Implementations/Lists/DLinkedList.h

        # Archivos de encabezado de estructuras concretas: Árboles
        include/Structures/Implementations/Trees/AVLTree.h
        include/Structures/Implementations/Trees/BSTree.h
        include/Structures/Implementations/Trees/SplayTree.h

        # Archivos de nodos
        include/Structures/Common/Nodes/BSTNode.h
        include/Structures/Common/Nodes/DNode.h
        include/Structures/Common/Nodes/SNode.h

        # Archivos adicionales
        include/Structures/Common/KVPair.h
)

# Incluir directorios con rutas cortas
target_include_directories(DataStructures PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)