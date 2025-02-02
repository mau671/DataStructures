/**
 * @file HashTable.h
 * @brief Clase que implementa una tabla de hash genérica utilizando encadenamiento para manejar colisiones.
 *
 * Permite insertar, eliminar y recuperar pares clave-valor.
 *
 * @author Profesor Mauricio Aviles Cisneros
 */

#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include "Structures/Implementations/Lists/DLinkedList.h"
#include "Structures/Common/KVPair.h"
#include "Structures/Abstract/Dictionary.h"

using std::runtime_error;
using std::cout;
using std::endl;
using std::string;

template <typename K, typename V>
class HashTable : public Dictionary<K, V> {
private:
    DLinkedList<KVPair<K, V>> *buckets; ///< Arreglo de listas enlazadas que almacenan pares clave-valor.
    int max; ///< Capacidad máxima de la tabla.
    int size; ///< Número actual de elementos en la tabla.
    double maxLoad; ///< Factor de carga máximo permitido.
    double minLoad; ///< Factor de carga mínimo permitido.
    DLinkedList<int> *primes; ///< Lista de números primos para el tamaño de la tabla.

    // Carga números primos para ser usados como capacidad máxima de la tabla. Inicia en 1021.
    void initPrimes() {
        primes = new DLinkedList<int>();
        primes->append(61);
        primes->append(127);
        primes->append(251);
        primes->append(509);
        primes->append(1021);
        primes->append(2039);
        primes->append(4073);
        primes->append(8147);
        primes->append(16273);
        primes->append(32537);
        primes->append(65071);
        primes->append(130147);
        primes->append(260339);
        primes->append(520679);
        primes->append(1041349);
        primes->append(2082709);
        primes->goToPos(4);
    }

    /** 
     * @brief Calcula el factor de carga actual de la tabla de hash.
     * 
     * @return El factor de carga.
     */
    double loadFactor() {
        return (double)size / (double)max;
    }

    // Redimensiona la tabla para hacerla más grande.
    void reHashUp() {
        primes->next();
        int newMax = primes->getElement();
        reHash(newMax);
    }

    // Redimensiona la tabla para hacerla más pequeña.
    void reHashDown() {
        primes->previous();
        int newMax = primes->getElement();
        if (newMax != max)
            reHash(newMax);
    }

    // Redimensiona la tabla al tamaño indicado.
    void reHash(int newMax) {
        int oldMax = max;
        max = newMax;
        DLinkedList<KVPair<K, V>> *newBuckets = new DLinkedList<KVPair<K, V>>[max];
        for (int i = 0; i < oldMax; i++) {
            buckets[i].goToStart();
            while (!buckets[i].getSize() == 0) {
                KVPair<K, V> p = buckets[i].remove();
                newBuckets[h(p.key)].append(p);
            }
        }
        delete [] buckets;
        buckets = newBuckets;
    }

    // Revisa que una llave no exista en la estructura.
    // Si la encuentra, lanza un error.
    // Si no la encuentra, la posición actual queda al final.
    void checkNotExisting(K key) {
        KVPair<K, V> p(key);
        if (buckets[h(key)].contains(p))
            throw runtime_error("Duplicated key.");
    }

    // Revisa que una llave exista en la estructura.
    // Si la encuentra, deja la posición actual apuntando a la llave buscada.
    // Si no la encuentra, lanza un error.
    void checkExisting(K key) {
        KVPair<K, V> p(key);
        if (!buckets[h(key)].contains(p))
            throw runtime_error("Key not found.");
    }

    /** 
     * @brief Función hash para convertir la clave en un índice de la tabla.
     * 
     * @param key La clave a hashear.
     * @return El índice correspondiente en la tabla.
     */
    int h(K key) {
        return compress(hashCodePolynomial(key));
    }

    /** 
     * @brief Comprime el código hash a un índice válido.
     * 
     * @param code El código hash a comprimir.
     * @return El índice comprimido.
     */
    int compress(int code) {
        int a = 1097;
        int b = 1279;
        return abs(a * code + b) % max;
    }

    template <typename T>
    /** 
     * @brief Calcula el código hash utilizando un enfoque polinómico.
     * 
     * @param key La clave a hashear.
     * @return El código hash calculado.
     */
    int hashCodePolynomial(T key) {
        int a = 33;
        int result = 0;
        char* bytes = reinterpret_cast<char*>(&key);
        for (unsigned int i = 0; i < sizeof(T); i++) {
            result += static_cast<int>(bytes[i] * pow(a, i));
        }
        return result;
    }

    /** 
     * @brief Sobrecarga de la función hash para cadenas de texto.
     * 
     * @param key La cadena a hashear.
     * @return El código hash calculado.
     */
    int hashCodePolynomial(string key) {
        int a = 33;
        int result = 0;
        for (unsigned int i = 0; i < key.size(); i++) {
            result += (int)key[i] * pow(a, i);
        }
        return result;
    }

public:
    /** 
     * @brief Constructor por defecto que inicializa la tabla de hash.
     */
    HashTable() {
        initPrimes();
        max = primes->getElement();
        buckets = new DLinkedList<KVPair<K, V>>[max];
        size = 0;
        maxLoad = 0.6;
        minLoad = 0.2;
    }

    /** 
     * @brief Destructor que libera la memoria utilizada por la tabla de hash.
     */
    ~HashTable() {
        delete [] buckets;
        delete primes;
    }

    /** 
     * @brief Inserta un nuevo par clave-valor en la tabla de hash.
     * 
     * @param key La clave del par.
     * @param value El valor asociado a la clave.
     * @throw runtime_error si la clave ya existe en la tabla.
     */
    void insert(K key, V value) {
        if (loadFactor() > maxLoad)
            reHashUp();
        checkNotExisting(key);
        KVPair<K, V> p(key, value);
        buckets[h(key)].append(p);
        size++;
    }

    /** 
     * @brief Elimina un elemento de la tabla de hash por su clave.
     * 
     * @param key La clave del elemento a eliminar.
     * @return El valor asociado a la clave eliminada.
     * @throw runtime_error si la clave no existe en la tabla.
     */
    V remove(K key) {
        if (loadFactor() <= minLoad)
            reHashDown();
        checkExisting(key);
        KVPair<K, V> p = buckets[h(key)].remove();
        size--;
        return p.value;
    }

    /** 
     * @brief Recupera el valor asociado a una clave.
     * 
     * @param key La clave del elemento a buscar.
     * @return El valor asociado a la clave.
     * @throw runtime_error si la clave no existe en la tabla.
     */
    V getValue(K key) {
        checkExisting(key);
        KVPair<K, V> p = buckets[h(key)].getElement();
        return p.value;
    }

    /** 
     * @brief Establece un nuevo valor para una clave existente.
     * 
     * @param key La clave del elemento a actualizar.
     * @param value El nuevo valor a establecer.
     * @throw runtime_error si la clave no existe en la tabla.
     */
    void setValue(K key, V value) {
        checkExisting(key);
        KVPair<K, V> p(key, value);
        buckets[h(key)].set(p);
    }

    /** 
     * @brief Verifica si la tabla contiene una clave específica.
     * 
     * @param key La clave a buscar.
     * @return true si la clave existe en la tabla, false en caso contrario.
     */
    bool contains(K key) {
        KVPair<K, V> p(key);
        return buckets[h(key)].contains(p);
    }

    /** 
     * @brief Elimina todos los elementos de la tabla de hash.
     */
    void clear() {
        for (int i = 0; i < max; i++) {
            buckets[i].clear();
        }
        size = 0;
    }

    /** 
     * @brief Recupera una lista de todas las claves en la tabla de hash.
     * 
     * @return Un puntero a una lista que contiene todas las claves.
     */
    List<K>* getKeys() {
        List<K> *keys = new DLinkedList<K>();
        for (int i = 0; i < max; i++) {
            buckets[i].goToStart();
            while (!buckets[i].atEnd()) {
                KVPair<K, V> p = buckets[i].getElement();
                keys->append(p.key);
                buckets[i].next();
            }
        }
        return keys;
    }

    /** 
     * @brief Recupera una lista de todos los valores en la tabla de hash.
     * 
     * @return Un puntero a una lista que contiene todos los valores.
     */
    List<V>* getValues() {
        List<V> *values = new DLinkedList<V>();
        for (int i = 0; i < max; i++) {
            buckets[i].goToStart();
            while (!buckets[i].atEnd()) {
                KVPair<K, V> p = buckets[i].getElement();
                values->append(p.value);
                buckets[i].next();
            }
        }
        return values;
    }

    /** 
     * @brief Obtiene el número de elementos en la tabla de hash.
     * 
     * @return El tamaño de la tabla de hash.
     */
    int getSize() {
        return size;
    }

    /** 
     * @brief Imprime el contenido de la tabla de hash.
     */
    void print() {
        cout << "[";
        for (int i = 0; i < max; i++) {
            buckets[i].goToStart();
            while (!buckets[i].atEnd()) {
                cout << buckets[i].getElement() << " ";
                buckets[i].next();
            }
        }
        cout << "]" << endl;
    }
};
