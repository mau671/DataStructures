/**
 * @file LinkedPriorityQueue.h
 * @brief Implementación de una cola de prioridad utilizando un arreglo de colas enlazadas.
 *
 * Esta clase implementa una cola de prioridad utilizando un arreglo de colas enlazadas (`LinkedQueue`).
 * Cada prioridad tiene su propia cola, y los elementos se insertan en la cola correspondiente a su prioridad.
 * La extracción de elementos sigue el orden de menor a mayor prioridad.
 *
 * @author Profesor Mauricio Aviles Cisneros
 * @author Mauricio González Prendas
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include "Structures/Abstract/Queue.h"
#include "Structures/Abstract/PriorityQueue.h"

using std::cout;
using std::endl;
using std::runtime_error;

/**
 * @brief Implementación de una cola de prioridad basada en colas enlazadas.
 * 
 * @tparam E Tipo de dato almacenado en la cola de prioridad.
 */
template <typename E>
class LinkedPriorityQueue : public PriorityQueue<E> {
private:
    LinkedQueue<E>* queues; ///< Arreglo de colas enlazadas, una por cada nivel de prioridad.
    int size; ///< Cantidad de elementos en la cola de prioridad.
    int priorities; ///< Número de niveles de prioridad disponibles.

public:
    /**
     * @brief Constructor que inicializa la cola de prioridad con un número de prioridades.
     * 
     * @param priorities Número de prioridades disponibles en la cola.
     * @throws std::runtime_error si priorities es menor o igual a 0.
     */
    LinkedPriorityQueue(int priorities) {
        if (priorities <= 0) throw runtime_error("Invalid number of priorities");
        queues = new LinkedQueue<E>[priorities];
        size = 0;
        this->priorities = priorities;
    }

    /**
     * @brief Destructor que libera la memoria utilizada por el arreglo de colas enlazadas.
     */
    ~LinkedPriorityQueue() {
        delete[] queues;
    }

    /**
     * @brief Inserta un elemento en la cola de prioridad con la prioridad especificada.
     * 
     * @param element Elemento a insertar.
     * @param priority Prioridad del elemento (por defecto 0).
     * @throws std::runtime_error si la prioridad está fuera del rango permitido.
     */
    void insert(E element, int priority = 0) {
        if (priority < 0 || priority >= priorities) throw runtime_error("Invalid priority");
        queues[priority].enqueue(element);
        size++;
    }

    /**
     * @brief Obtiene el elemento con la mayor prioridad sin eliminarlo.
     * 
     * @return Elemento con la mayor prioridad disponible.
     * @throws std::runtime_error si la cola está vacía.
     */
    E min() {
        if (size == 0) throw runtime_error("Queue is empty");
        for (int i = 0; i < priorities; i++) {
            if (!queues[i].isEmpty()) return queues[i].frontValue();
        }
        throw runtime_error("Queue not found");
    }

    /**
     * @brief Elimina y retorna el elemento con la mayor prioridad.
     * 
     * @return Elemento con la mayor prioridad disponible.
     * @throws std::runtime_error si la cola está vacía.
     */
    E removeMin() {
        if (size == 0) throw runtime_error("Queue is empty");
        for (int i = 0; i < priorities; i++) {
            if (!queues[i].isEmpty()) {
                size--;
                return queues[i].dequeue();
            }
        }
        throw runtime_error("Queue not found");
    }

    /**
     * @brief Retorna el número de elementos en la cola de prioridad.
     * 
     * @return Cantidad de elementos en la cola.
     */
    int getSize() {
        return size;
    }

    /**
     * @brief Verifica si la cola de prioridad está vacía.
     * 
     * @return true si la cola está vacía, false en caso contrario.
     */
    bool isEmpty() {
        return size == 0;
    }

    /**
     * @brief Elimina todos los elementos de la cola de prioridad.
     */
    void clear() {
        for (int i = 0; i < priorities; i++) {
            queues[i].clear();
        }
        size = 0;
    }

    /**
     * @brief Imprime el contenido de la cola de prioridad.
     */
    void print() {
        for (int i = 0; i < priorities; i++) {
            cout << "Priority " << i << ": ";
            queues[i].print();
        }
    }
};
