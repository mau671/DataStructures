/**
 * @file LinkedQueue.h
 * @brief Implementación de una cola enlazada genérica.
 *
 * Esta clase implementa una estructura de datos de tipo cola utilizando nodos enlazados.
 * Admite operaciones estándar de una cola (FIFO), así como algunas funciones adicionales
 * para soportar operaciones de una deque (cola de doble extremo).
 *
 * @tparam E Tipo de dato almacenado en la cola.
 * @author Mauricio González Prendas
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include "Structures/Abstract/Queue.h"
#include "Structures/Common/Nodes/Node.h"

using std::cout;
using std::endl;
using std::runtime_error;

/**
 * @class LinkedQueue
 * @brief Implementación de una cola basada en nodos enlazados.
 *
 * Esta clase implementa una cola genérica enlazada, proporcionando operaciones 
 * como inserción, eliminación y consulta de elementos.
 *
 * @tparam E Tipo de dato almacenado en la cola.
 */
template <typename E>
class LinkedQueue : public Queue<E> {
private:
    Node<E>* front; ///< Puntero al nodo ficticio (cabeza) de la cola.
    Node<E>* back;  ///< Puntero al último nodo de la cola.
    int size;       ///< Número de elementos en la cola.

public:
    /**
     * @brief Constructor por defecto. Inicializa una cola vacía.
     */
    LinkedQueue() {
        front = back = new Node<E>(); ///< Nodo ficticio para simplificar operaciones.
        size = 0;
    }

    /**
     * @brief Destructor de la cola. Libera la memoria de los nodos.
     */
    ~LinkedQueue() {
        clear();
        delete front;
    }

    /**
     * @brief Inserta un elemento al final de la cola.
     * 
     * @param element Elemento a insertar.
     */
    void enqueue(E element) {
        back = back->next = new Node<E>(element);
        size++;
    }

    /**
     * @brief Elimina y retorna el elemento al frente de la cola.
     * 
     * @return Elemento en el frente de la cola.
     * @throws std::runtime_error si la cola está vacía.
     */
    E dequeue() {
        if (size == 0) throw runtime_error("Queue is empty");
        Node<E>* temp = front->next;
        E result = temp->element;
        front->next = temp->next;
        delete temp;
        size--;
        if (size == 0) back = front;
        return result;
    }

    /**
     * @brief Retorna el elemento en el frente de la cola sin eliminarlo.
     * 
     * @return Elemento en el frente de la cola.
     * @throws std::runtime_error si la cola está vacía.
     */
    E frontValue() {
        if (size == 0) throw runtime_error("Queue is empty");
        return front->next->element;
    }

    /**
     * @brief Elimina todos los elementos de la cola.
     */
    void clear() {
        while (front->next != nullptr) {
            Node<E>* temp = front->next;
            front->next = temp->next;
            delete temp;
        }
        back = front;
        size = 0;
    }

    /**
     * @brief Verifica si la cola está vacía.
     * 
     * @return true si la cola está vacía, false en caso contrario.
     */
    bool isEmpty() {
        return size == 0;
    }

    /**
     * @brief Obtiene el número de elementos en la cola.
     * 
     * @return Número de elementos en la cola.
     */
    int getSize() {
        return size;
    }

    /**
     * @brief Inserta un elemento al frente de la cola (soporte para Deque).
     * 
     * @param element Elemento a insertar al frente.
     */
    void enqueueFront(E element) {
        Node<E>* newNode = new Node<E>(element);
        newNode->next = front->next;
        front->next = newNode;
        if (size == 0) {
            back = newNode;
        }
        size++;
    }

    /**
     * @brief Elimina y retorna el último elemento de la cola (soporte para Deque).
     * 
     * @return Elemento en el final de la cola.
     * @throws std::runtime_error si la cola está vacía.
     */
    E dequeueBack() {
        if (size == 0) throw runtime_error("Queue is empty");
        Node<E>* temp = front;
        while (temp->next != back) {
            temp = temp->next;
        }
        E result = back->element;
        delete back;
        back = temp;
        back->next = nullptr;
        size--;
        return result;
    }

    /**
     * @brief Retorna el elemento en el final de la cola sin eliminarlo.
     * 
     * @return Elemento en el final de la cola.
     * @throws std::runtime_error si la cola está vacía.
     */
    E backValue() {
        if (size == 0) throw runtime_error("Queue is empty");
        return back->element;
    }

    /**
     * @brief Imprime los elementos de la cola en orden.
     */
    void print() {
        cout << "[ ";
        Node<E>* temp = front->next;
        while (temp != nullptr) {
            cout << temp->element << " ";
            temp = temp->next;
        }
        cout << "]" << endl;
    }
};
