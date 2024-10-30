# Directorio de cabeceras y archivos fuente
INCLUDE_DIR = /home/mau/Escritorio/tec/ED/DataStructures/include
SRC_DIR = src/Dictionaries
BIN_DIR = bin

# Compilador y opciones de compilación
CXX = g++
CXXFLAGS = -I$(INCLUDE_DIR) -std=c++11

# Archivos fuente y ejecutables
SOURCES = $(SRC_DIR)/AVLDictionaryTest.cpp $(SRC_DIR)/BSTDictionaryTest.cpp $(SRC_DIR)/HashTableTest.cpp $(SRC_DIR)/UnsortedArrayDictionaryTest.cpp
EXECUTABLES = $(BIN_DIR)/AVLDictionaryTest $(BIN_DIR)/BSTDictionaryTest $(BIN_DIR)/HashTableTest $(BIN_DIR)/UnsortedArrayDictionaryTest

# Regla para compilar todos los ejecutables
all: $(EXECUTABLES)

# Crear directorio bin si no existe
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Reglas para compilar cada prueba en un ejecutable separado
$(BIN_DIR)/AVLDictionaryTest: $(SRC_DIR)/AVLDictionaryTest.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN_DIR)/BSTDictionaryTest: $(SRC_DIR)/BSTDictionaryTest.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN_DIR)/HashTableTest: $(SRC_DIR)/HashTableTest.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN_DIR)/UnsortedArrayDictionaryTest: $(SRC_DIR)/UnsortedArrayDictionaryTest.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Limpiar archivos generados
clean:
	rm -f $(EXECUTABLES)
