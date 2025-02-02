/*
 * Archivo: BSTDictionary.h
 * Descripción: Clase que implementa un diccionario utilizando un árbol binario de búsqueda (BST).
 *              Permite insertar, eliminar y recuperar pares clave-valor.
 *
 * Autor(es): Profesor Mauricio Aviles Cisneros
 */

#pragma once

#include <stdexcept>
#include "Structures/Abstract/Dictionary.h"
#include "Structures/Common/KVPair.h"
#include "Structures/Implementations/Trees/BSTree.h"
#include "Structures/Implementations/Lists/DLinkedList.h"

template <typename K, typename V>
class BSTDictionary : public Dictionary<K, V> {
private:
    BSTree<KVPair<K, V>>* pairs; ///< Árbol binario de búsqueda que almacena los pares clave-valor.

public:
    /** 
     * @brief Constructor de copia (eliminado).
     */
    BSTDictionary(const BSTDictionary<K, V>& other) = delete;

    /** 
     * @brief Operador de asignación (eliminado).
     */
    void operator =(const BSTDictionary<K, V>& other) = delete;

    /** 
     * @brief Constructor por defecto.
     * 
     * Inicializa un árbol binario de búsqueda vacío para almacenar pares clave-valor.
     */
    BSTDictionary() {
        pairs = new BSTree<KVPair<K, V>>();
    }

    /** 
     * @brief Destructor.
     * 
     * Libera los recursos utilizados por el árbol binario de búsqueda.
     */
    ~BSTDictionary() {
        delete pairs;
    }

    /** 
     * @brief Inserta un nuevo par clave-valor en el diccionario.
     * 
     * @param key La clave del par.
     * @param value El valor asociado a la clave.
     */
    void insert(K key, V value) {
        KVPair<K, V> p(key, value);
        pairs->insert(p);
    }

    /** 
     * @brief Elimina un elemento del diccionario por su clave.
     * 
     * @param key La clave del elemento a eliminar.
     * @return El valor asociado a la clave eliminada.
     * @throw std::runtime_error si la clave no existe en el diccionario.
     */
    V remove(K key) {
        KVPair<K, V> p(key);
        p = pairs->remove(p);
        return p.value;
    }

    /** 
     * @brief Recupera el valor asociado a una clave.
     * 
     * @param key La clave del elemento a buscar.
     * @return El valor asociado a la clave.
     * @throw std::runtime_error si la clave no existe en el diccionario.
     */
    V getValue(K key) {
        KVPair<K, V> p(key);
        p = pairs->find(p);
        return p.value;
    }

    /** 
     * @brief Establece un nuevo valor para una clave existente.
     * 
     * @param key La clave del elemento a actualizar.
     * @param value El nuevo valor a establecer.
     */
    void setValue(K key, V value) {
        KVPair<K, V> p(key, value);
        pairs->remove(p);
        pairs->insert(p);
    }

    /** 
     * @brief Verifica si el diccionario contiene una clave específica.
     * 
     * @param key La clave a buscar.
     * @return true si la clave existe en el diccionario, false en caso contrario.
     */
    bool contains(K key) {
        KVPair<K, V> p(key);
        return pairs->contains(p);
    }

    /** 
     * @brief Recupera una lista de todas las claves en el diccionario.
     * 
     * @return Un puntero a una lista que contiene todas las claves.
     */
    List<K>* getKeys() {
        List<KVPair<K, V>>* items = pairs->getElements();
        List<K>* keys = new DLinkedList<K>();
        while (!items->atEnd()) {
            auto p = items->getElement();
            keys->append(p.key);
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
            auto p = items->getElement();
            values->append(p.value);
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
