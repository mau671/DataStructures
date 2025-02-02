/**
 * @file Dictionary.h
 * @brief Clase abstracta que define la interfaz para un diccionario genérico.
 *
 * Esta clase representa un diccionario que mapea claves de tipo K a valores de tipo V.
 * Proporciona una interfaz común para operaciones básicas como inserción, eliminación
 * y recuperación de pares clave-valor. Las clases derivadas deben implementar estos
 * métodos para proporcionar un comportamiento concreto.
 *
 * @author Profesor Mauricio Aviles Cisneros
 * @author Mauricio González Prendas
 */

#pragma once

#include "Structures/Abstract/List.h"

/**
 * @brief Clase abstracta que define la interfaz para un diccionario.
 *
 * Esta clase representa un diccionario genérico que mapea claves de tipo K a valores de tipo V.
 * Proporciona una interfaz común para operaciones básicas como inserción, eliminación
 * y recuperación de pares clave-valor. Las clases derivadas deben implementar estos
 * métodos para proporcionar un comportamiento concreto.
 *
 * @tparam K Tipo de las claves del diccionario.
 * @tparam V Tipo de los valores del diccionario.
 */
template <typename K, typename V>
class Dictionary {
private:
    // Constructor de copia privado para evitar copias no deseadas.
    Dictionary(const Dictionary<K, V>& other) {}

    // Operador de asignación privado para evitar asignaciones no deseadas.
    void operator=(const Dictionary<K, V>& other) {}

public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa un diccionario vacío.
     */
    Dictionary() {}

    /**
     * @brief Destructor virtual.
     *
     * Asegura que los recursos se liberen correctamente en las clases derivadas.
     */
    virtual ~Dictionary() {}

    /**
     * @brief Inserta un par clave-valor en el diccionario.
     *
     * @param key La clave a insertar.
     * @param value El valor asociado a la clave.
     */
    virtual void insert(K key, V value) = 0;

    /**
     * @brief Elimina un elemento del diccionario usando la clave.
     *
     * @param key La clave del elemento a eliminar.
     * @return El valor asociado a la clave eliminada.
     */
    virtual V remove(K key) = 0;

    /**
     * @brief Recupera el valor asociado a una clave.
     *
     * @param key La clave cuyo valor se desea obtener.
     * @return El valor asociado a la clave.
     */
    virtual V getValue(K key) = 0;

    /**
     * @brief Establece o actualiza el valor asociado a una clave.
     *
     * Si la clave ya existe, su valor se actualiza. Si no existe, se inserta un nuevo par.
     *
     * @param key La clave cuyo valor se desea establecer o actualizar.
     * @param value El nuevo valor a asociar con la clave.
     */
    virtual void setValue(K key, V value) = 0;

    /**
     * @brief Verifica si el diccionario contiene una clave específica.
     *
     * @param key La clave a verificar.
     * @return true si la clave existe, false en caso contrario.
     */
    virtual bool contains(K key) = 0;

    /**
     * @brief Recupera una lista de todas las claves en el diccionario.
     *
     * @return Un puntero a una lista que contiene todas las claves.
     */
    virtual List<K>* getKeys() = 0;

    /**
     * @brief Recupera una lista de todos los valores en el diccionario.
     *
     * @return Un puntero a una lista que contiene todos los valores.
     */
    virtual List<V>* getValues() = 0;

    /**
     * @brief Obtiene el número de elementos en el diccionario.
     *
     * @return El tamaño del diccionario.
     */
    virtual int getSize() = 0;

    /**
     * @brief Imprime el contenido del diccionario.
     *
     * Este método debe ser implementado para mostrar el estado del diccionario.
     */
    virtual void print() = 0;
};