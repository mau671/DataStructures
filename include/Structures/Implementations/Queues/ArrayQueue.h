/**
 * @file ArrayQueue.h
 * @brief Implementación de una cola utilizando un arreglo circular.
 *
 * Esta clase proporciona operaciones para insertar, eliminar y consultar elementos
 * de una cola basada en un arreglo circular de tamaño fijo.
 *
 * @author Profesor Mauricio Aviles Cisneros
 * @author Mauricio González Prendas
 */

#pragma once

#include <stdexcept>
#include <iostream>
#include "Structures/Abstract/Queue.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Implementación de una cola (Queue) utilizando un arreglo circular.
 * 
 * Esta clase proporciona operaciones para insertar, eliminar y consultar elementos
 * de una cola basada en un arreglo circular de tamaño fijo.
 * 
 * @tparam E Tipo de dato almacenado en la cola.
 */
template <typename E>
class ArrayQueue : public Queue<E> {
private:
    E* elements; ///< Arreglo dinámico para almacenar los elementos de la cola.
    int front;   ///< Índice del primer elemento en la cola.
    int back;    ///< Índice del último elemento insertado en la cola.
    int size;    ///< Número actual de elementos en la cola.
    int max;     ///< Capacidad máxima de la cola.

public:
    /**
     * @brief Constructor de la cola con tamaño máximo especificado.
     * 
     * @param max Capacidad máxima de la cola (por defecto DEFAULT_MAX).
     * @throw runtime_error si el tamaño máximo es menor que 1.
     */
    ArrayQueue(int max = DEFAULT_MAX) {
        if (max < 1)
            throw runtime_error("Invalid max size.");
        elements = new E[max];
        size = back = front = 0;
        this->max = max;
    }

    /**
     * @brief Destructor que libera la memoria utilizada por la cola.
     */
    ~ArrayQueue() {
        delete[] elements;
    }

    /**
     * @brief Inserta un elemento al final de la cola.
     * 
     * @param element Elemento a insertar.
     * @throw runtime_error si la cola está llena.
     */
    void enqueue(E element) {
        if (size == max)
            throw runtime_error("Queue is full.");
        elements[back] = element;
        back = (back + 1) % max;
        size++;
    }

    /**
     * @brief Elimina y retorna el elemento en el frente de la cola.
     * 
     * @return Elemento eliminado de la cola.
     * @throw runtime_error si la cola está vacía.
     */
    E dequeue() {
        if (size == 0)
            throw runtime_error("Queue is empty.");
        front = (front + 1) % max;
        size--;
        return elements[(front + max - 1) % max];
    }

    /**
     * @brief Retorna el elemento en el frente de la cola sin eliminarlo.
     * 
     * @return Elemento en el frente de la cola.
     * @throw runtime_error si la cola está vacía.
     */
    E frontValue() {
        if (size == 0)
            throw runtime_error("Queue is empty.");
        return elements[front];
    }

    /**
     * @brief Elimina todos los elementos de la cola.
     */
    void clear() {
        size = back = front = 0;
    }

    /**
     * @brief Verifica si la cola está vacía.
     * 
     * @return true si la cola no contiene elementos, false en caso contrario.
     */
    bool isEmpty() {
        return size == 0;
    }

    /**
     * @brief Retorna el número de elementos en la cola.
     * 
     * @return La cantidad de elementos en la cola.
     */
    int getSize() {
        return size;
    }

    /**
     * @brief Imprime el contenido de la cola.
     */
    void print() {
        cout << "[ ";
        int pos = front;
        for (int i = 0; i < size; i++) {
            cout << elements[pos] << " ";
            pos = (pos + 1) % max;
        }
        cout << "]" << endl;
    }
};
