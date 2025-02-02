/**
 * @file LinkedStack.h
 * @brief Implementación de una pila (stack) utilizando una lista enlazada.
 *
 * Proporciona operaciones básicas de una pila, como push, pop, topValue, y otras utilidades.
 *
 * @author Profesor Mauricio Aviles Cisneros
 */

#pragma once

#include <stdexcept>
#include <iostream>
#include "Structures/Abstract/Stack.h"
#include "Structures/Common/Nodes/Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Clase plantilla que implementa una pila utilizando una lista enlazada.
 *
 * Esta clase permite almacenar elementos en una estructura de pila (LIFO: Last In, First Out)
 * utilizando nodos enlazados dinámicamente.
 *
 * @tparam E Tipo de dato almacenado en la pila.
 */
template <typename E>
class LinkedStack : public Stack<E> {
private:
    Node<E>* top; ///< Puntero al nodo en la parte superior de la pila.
    int size;     ///< Número de elementos actualmente en la pila.

public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa la pila vacía.
     */
    LinkedStack() {
        top = nullptr;
        size = 0;
    }

    /**
     * @brief Destructor.
     *
     * Libera la memoria utilizada por todos los nodos de la pila.
     */
    ~LinkedStack() {
        clear();
    }

    /**
     * @brief Inserta un elemento en la parte superior de la pila.
     *
     * @param element Elemento a insertar en la pila.
     */
    void push(E element) {
        top = new Node<E>(element, top);
        size++;
    }

    /**
     * @brief Elimina y retorna el elemento en la parte superior de la pila.
     *
     * @return El elemento eliminado de la pila.
     * @throw runtime_error Si la pila está vacía.
     */
    E pop() {
        if (size == 0)
            throw runtime_error("Stack is empty.");
        E result = top->element;
        Node<E>* temp = top;
        top = top->next;
        delete temp;
        size--;
        return result;
    }

    /**
     * @brief Retorna el elemento en la parte superior de la pila sin eliminarlo.
     *
     * @return El elemento en la parte superior de la pila.
     * @throw runtime_error Si la pila está vacía.
     */
    E topValue() {
        if (size == 0)
            throw runtime_error("Stack is empty.");
        return top->element;
    }

    /**
     * @brief Elimina todos los elementos de la pila.
     *
     * Libera la memoria de todos los nodos y reinicia el tamaño a cero.
     */
    void clear() {
        while (top != nullptr) {
            Node<E>* temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
    }

    /**
     * @brief Verifica si la pila está vacía.
     *
     * @return true si la pila no contiene elementos, false en caso contrario.
     */
    bool isEmpty() {
        return size == 0;
    }

    /**
     * @brief Retorna el número de elementos en la pila.
     *
     * @return El tamaño actual de la pila.
     */
    int getSize() {
        return size;
    }

    /**
     * @brief Imprime el contenido de la pila.
     *
     * Muestra los elementos en el formato [ elemTop ... elemBottom ].
     */
    void print() {
        cout << "[ ";
        Node<E>* temp = top;
        while (temp != nullptr) {
            cout << temp->element << " ";
            temp = temp->next;
        }
        cout << "]" << endl;
    }
};