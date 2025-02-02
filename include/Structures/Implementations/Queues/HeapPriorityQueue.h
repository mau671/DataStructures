/**
 * @file HeapPriorityQueue.h
 * @brief Implementación de una cola de prioridad basada en un heap.
 *
 * Esta clase utiliza un heap mínimo (`MinHeap`) para almacenar pares clave-valor (`KVPair<int, E>`),
 * donde la clave representa la prioridad del elemento y el valor es el dato almacenado.
 *
 * @author Profesor Mauricio Aviles Cisneros
 */

#pragma once

#include <stdexcept>
#include "Structures/Abstract/PriorityQueue.h"
#include "Structures/Implementations/Queues/MinHeap.h"
#include "Structures/Common/KVPair.h"

/**
 * @brief Implementación de una cola de prioridad utilizando un heap mínimo.
 * 
 * @tparam E Tipo de dato almacenado en la cola de prioridad.
 */
template <typename E>
class HeapPriorityQueue : public PriorityQueue<E> {
private:
    MinHeap<KVPair<int, E>>* pairs; ///< Heap mínimo que almacena pares de prioridad y elementos.

public:
    /**
     * @brief Constructor de la cola de prioridad con tamaño máximo opcional.
     * 
     * @param max Capacidad máxima del heap (por defecto DEFAULT_MAX).
     */
    HeapPriorityQueue(int max = DEFAULT_MAX) {
        pairs = new MinHeap<KVPair<int, E>>(max);
    }

    /**
     * @brief Destructor que libera la memoria utilizada por el heap.
     */
    ~HeapPriorityQueue() {
        delete pairs;
    }

    /**
     * @brief Inserta un elemento en la cola de prioridad con una prioridad dada.
     * 
     * @param element Elemento a insertar.
     * @param priority Prioridad del elemento (menor valor significa mayor prioridad).
     */
    void insert(E element, int priority) {
        KVPair<int, E> p(priority, element);
        pairs->insert(p);
    }

    /**
     * @brief Obtiene el elemento con la menor prioridad sin eliminarlo.
     * 
     * @return Elemento con la mayor prioridad (menor clave).
     */
    E min() {
        KVPair<int, E> p = pairs->first();
        return p.value;
    }

    /**
     * @brief Elimina y retorna el elemento con la menor prioridad.
     * 
     * @return Elemento con la mayor prioridad (menor clave).
     */
    E removeMin() {
        KVPair<int, E> p = pairs->removeFirst();
        return p.value;
    }

    /**
     * @brief Elimina todos los elementos de la cola de prioridad.
     */
    void clear() {
        pairs->clear();
    }

    /**
     * @brief Retorna el número de elementos en la cola de prioridad.
     * 
     * @return Cantidad de elementos en la cola.
     */
    int getSize() {
        return pairs->getSize();
    }

    /**
     * @brief Verifica si la cola de prioridad está vacía.
     * 
     * @return true si la cola está vacía, false en caso contrario.
     */
    bool isEmpty() {
        return pairs->isEmpty();
    }

    /**
     * @brief Imprime el contenido de la cola de prioridad.
     */
    void print() {
        pairs->print();
    }
};