/**
 * @file UnsortedArrayDictionary.h
 * @brief Clase que implementa un diccionario no ordenado utilizando un arreglo.
 *
 * Permite insertar, eliminar y recuperar pares clave-valor.
 *
 * @author Profesor Mauricio Aviles Cisneros
 */

#pragma once

#include <stdexcept>
#include "Structures/Abstract/Dictionary.h"
#include "Structures/Implementations/Lists/ArrayList.h"
#include "Structures/Implementations/Lists/DLinkedList.h"
#include "Structures/Common/KVPair.h"

using std::runtime_error;

template <typename K, typename V>
class UnsortedArrayDictionary : public Dictionary<K, V> {
private:
    List<KVPair<K, V>>* pairs; ///< Lista de pares clave-valor almacenados en el diccionario.

    /** 
     * @brief Verifica que una clave no exista en el diccionario.
     * 
     * @param key La clave a verificar.
     * @throw runtime_error si la clave ya existe en el diccionario.
     */
    void checkNotExisting(K key) {
        KVPair<K, V> p(key);
        pairs->goToStart();
        while (!pairs->atEnd()) {
            if (p == pairs->getElement())
                throw runtime_error("Duplicated key.");
            pairs->next();
        }
    }

    /**
     * @brief Verifica que una clave exista en el diccionario.
     * 
     * Si la clave existe, la posición actual se actualiza para apuntar al par correspondiente.
     * 
     * @param key La clave a verificar.
     * @throw runtime_error si la clave no se encuentra en el diccionario.
     */
    void checkExisting(K key) {
        KVPair<K, V> p(key);
        pairs->goToStart();
        while (!pairs->atEnd()) {
            if (p == pairs->getElement())
                return;
            pairs->next();
        }
        throw runtime_error("Key not found.");
    }

public:
    /**
     * @brief Constructor que inicializa el diccionario con un tamaño máximo.
     * 
     * @param max El tamaño máximo del diccionario (por defecto es DEFAULT_MAX).
     */
    UnsortedArrayDictionary(int max = DEFAULT_MAX) {
        pairs = new ArrayList<KVPair<K, V>>(max);
    }

    /**
     * @brief Destructor que libera los recursos utilizados por el diccionario.
     */
    ~UnsortedArrayDictionary() {
        delete pairs;
    }

    /** 
     * @brief Inserta un nuevo par clave-valor en el diccionario.
     * 
     * @param key La clave del par.
     * @param value El valor asociado a la clave.
     * @throw runtime_error si la clave ya existe en el diccionario.
     */
    void insert(K key, V value) {
        checkNotExisting(key);
        KVPair<K, V> p(key, value);
        pairs->append(p);
    }

    /** 
     * @brief Elimina un elemento del diccionario por su clave.
     * 
     * @param key La clave del elemento a eliminar.
     * @return El valor asociado a la clave eliminada.
     * @throw runtime_error si la clave no existe en el diccionario.
     */
    V remove(K key) {
        checkExisting(key);
        KVPair<K, V> p = pairs->remove();
        return p.value;
    }

    /** 
     * @brief Recupera el valor asociado a una clave.
     * 
     * @param key La clave del elemento a buscar.
     * @return El valor asociado a la clave.
     * @throw runtime_error si la clave no existe en el diccionario.
     */
    V getValue(K key) {
        checkExisting(key);
        KVPair<K, V> p = pairs->getElement();
        return p.value;
    }

    /** 
     * @brief Establece un nuevo valor para una clave existente.
     * 
     * @param key La clave del elemento a actualizar.
     * @param value El nuevo valor a establecer.
     * @throw runtime_error si la clave no existe en el diccionario.
     */
    void setValue(K key, V value) {
        checkExisting(key);
        KVPair<K, V> p(key, value);
        pairs->set(p);
    }

    /** 
     * @brief Verifica si el diccionario contiene una clave específica.
     * 
     * @param key La clave a buscar.
     * @return true si la clave existe en el diccionario, false en caso contrario.
     */
    bool contains(K key) {
        KVPair<K, V> p(key);
        pairs->goToStart();
        while (!pairs->atEnd()) {
            if (p == pairs->getElement())
                return true;
            pairs->next();
        }
        return false;
    }

    /** 
     * @brief Recupera una lista de todas las claves en el diccionario.
     * 
     * @return Un puntero a una lista que contiene todas las claves.
     */
    List<K>* getKeys() {
        List<K>* keys = new DLinkedList<K>();
        pairs->goToStart();
        while (!pairs->atEnd()) {
            KVPair<K, V> p = pairs->getElement();
            keys->append(p.key);
            pairs->next();
        }
        return keys;
    }

    /** 
     * @brief Recupera una lista de todos los valores en el diccionario.
     * 
     * @return Un puntero a una lista que contiene todos los valores.
     */
    List<V>* getValues() {
        List<V>* values = new DLinkedList<V>();
        pairs->goToStart();
        while (!pairs->atEnd()) {
            KVPair<K, V> p = pairs->getElement();
            values->append(p.value);
            pairs->next();
        }
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
