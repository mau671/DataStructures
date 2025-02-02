/**
 * @file SplayDictionary.h
 * @brief Clase que implementa un diccionario utilizando un árbol Splay.
 *
 * Permite insertar, eliminar y recuperar pares clave-valor.
 *
 * @author Profesor Mauricio Aviles Cisneros
 * @author Mauricio González Prendas
 * @author Josué Meza Solano
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include "Structures/Abstract/Dictionary.h"
#include "Structures/Common/KVPair.h"
#include "Structures/Implementations/Trees/SplayTree.h"
#include "Structures/Implementations/Lists/DLinkedList.h"

template <typename K, typename V>
class SplayDictionary : public Dictionary<K, V> {
private:
    SplayTree<KVPair<K, V>>* pairs; ///< Árbol Splay que almacena los pares clave-valor.

public:
    /** 
     * @brief Constructor de copia (eliminado).
     */
    SplayDictionary(const SplayDictionary<K, V>& other) = delete;

    /** 
     * @brief Operador de asignación (eliminado).
     */
    void operator=(const SplayDictionary<K, V>& other) = delete;

    /** 
     * @brief Constructor por defecto.
     * 
     * Inicializa un árbol Splay vacío para almacenar pares clave-valor.
     */
    SplayDictionary() {
        pairs = new SplayTree<KVPair<K, V>>();
    }

    /** 
     * @brief Destructor.
     * 
     * Libera los recursos utilizados por el árbol Splay.
     */
    ~SplayDictionary() {
        delete pairs;
    }

    /** 
     * @brief Inserta un nuevo par clave-valor en el diccionario.
     * 
     * @param key La clave del par.
     * @param value El valor asociado a la clave.
     */
    void insert(K key, V value) {
        KVPair<K, V> pair(key, value);
        pairs->insert(pair);
    }

    /** 
     * @brief Elimina un elemento del diccionario por su clave.
     * 
     * @param key La clave del elemento a eliminar.
     * @return El valor asociado a la clave eliminada.
     * @throw std::runtime_error si la clave no existe en el diccionario.
     */
    V remove(K key) {
        KVPair<K, V> pair(key);
        pair = pairs->remove(pair);
        return pair.value;
    }

    /** 
     * @brief Recupera el valor asociado a una clave.
     * 
     * @param key La clave del elemento a buscar.
     * @return El valor asociado a la clave.
     * @throw std::runtime_error si la clave no existe en el diccionario.
     */
    V getValue(K key) {
        KVPair<K, V> pair(key);
        pair = pairs->find(pair);
        return pair.value;
    }

    /** 
     * @brief Establece un nuevo valor para una clave existente.
     * 
     * @param key La clave del elemento a actualizar.
     * @param value El nuevo valor a establecer.
     */
    void setValue(K key, V value) {
        KVPair<K, V> pair(key, value);
        pairs->remove(pair);
        pairs->insert(pair);
        
    }

    /** 
     * @brief Verifica si el diccionario contiene una clave específica.
     * 
     * @param key La clave a buscar.
     * @return true si la clave existe en el diccionario, false en caso contrario.
     */
    bool contains(K key) {
        KVPair<K, V> pair(key);
        return pairs->contains(pair);
    }

    /** 
     * @brief Recupera una lista de todas las claves en el diccionario.
     * 
     * @return Un puntero a una lista que contiene todas las claves.
     */
    List<K>* getKeys() {
        // Llama a una versión de getElements que no splayea el árbol en cada acceso.
        List<KVPair<K, V>>* items = pairs->getElements();

        List<K>* keys = new DLinkedList<K>();

        // Itera sobre los pares sin modificar la estructura del árbol.
        while (!items->atEnd()) {
            auto pair = items->getElement();
            keys->append(pair.key);
            items->next();
        }
        delete items;
        return keys;
    }

    /** 
     * @brief Recupera una lista de todos los valores en el diccionario.
     * 
     * @return Un puntero a una lista que contiene todos los valores.
     */
    List<V>* getValues() {
        List<KVPair<K, V>>* items = pairs->getElements();
        List<V>* values = new DLinkedList<V>();
        while (!items->atEnd()) {
            auto pair = items->getElement();
            values->append(pair.value);
            items->next();
        }
        delete items;
        return values;
    }

    /** 
     * @brief Obtiene el número de elementos en el diccionario.
     * 
     * @return El tamaño del diccionario.
     */
    int getSize() {
        return pairs->getSize();
    }

    /** 
     * @brief Imprime el contenido del diccionario.
     */
    void print() {
        pairs->print();
    }
};
