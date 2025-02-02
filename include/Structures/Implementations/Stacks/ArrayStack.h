/**
 * @file ArrayStack.h
 * @brief Implementación de una pila (stack) utilizando un arreglo dinámico.
 *
 * Proporciona operaciones básicas de una pila, como push, pop, topValue, y otras utilidades.
 *
 * @author Profesor Mauricio Aviles Cisneros
 */

#pragma once

#include <stdexcept>
#include <iostream>
#include "Structures/Abstract/Stack.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Clase plantilla que implementa una pila utilizando un arreglo dinámico.
 *
 * Esta clase permite almacenar elementos en una estructura de pila (LIFO: Last In, First Out)
 * con un tamaño máximo definido durante la inicialización.
 *
 * @tparam E Tipo de dato almacenado en la pila.
 */
template <typename E>
class ArrayStack : public Stack<E> {
private:
    E* elements; ///< Arreglo dinámico que almacena los elementos de la pila.
    int max;     ///< Capacidad máxima de la pila.
    int top;     ///< Índice del elemento en la parte superior de la pila.

public:
    /**
     * @brief Constructor que inicializa la pila con una capacidad máxima.
     *
     * @param max Capacidad máxima de la pila. Si no se especifica, se utiliza DEFAULT_MAX.
     * @throw runtime_error Si el tamaño máximo es menor que 1.
     */
    ArrayStack(int max = DEFAULT_MAX) {
        if (max < 1)
            throw runtime_error("Invalid max size.");
        elements = new E[max];
        this->max = max;
        top = 0;
    }

    /**
     * @brief Destructor que libera la memoria utilizada por el arreglo dinámico.
     */
    ~ArrayStack() {
        delete[] elements;
    }

    /**
     * @brief Inserta un elemento en la parte superior de la pila.
     *
     * @param element Elemento a insertar en la pila.
     * @throw runtime_error Si la pila está llena (desbordamiento).
     */
    void push(E element) {
        if (top == max)
            throw runtime_error("Stack overflow.");
        elements[top] = element;
        top++;
    }

    /**
     * @brief Elimina y retorna el elemento en la parte superior de la pila.
     *
     * @return El elemento eliminado de la pila.
     * @throw runtime_error Si la pila está vacía.
     */
    E pop() {
        if (top == 0)
            throw runtime_error("Stack is empty.");
        top--;
        return elements[top];
    }

    /**
     * @brief Retorna el elemento en la parte superior de la pila sin eliminarlo.
     *
     * @return El elemento en la parte superior de la pila.
     * @throw runtime_error Si la pila está vacía.
     */
    E topValue() {
        if (top == 0)
            throw runtime_error("Stack is empty.");
        return elements[top - 1];
    }

    /**
     * @brief Elimina todos los elementos de la pila.
     *
     * Reinicia el índice `top` a cero, indicando que la pila está vacía.
     */
    void clear() {
        top = 0;
        //delete[] elements;
        //elements = new E[max];
    }

    /**
     * @brief Verifica si la pila está vacía.
     *
     * @return true si la pila no contiene elementos, false en caso contrario.
     */
    bool isEmpty() {
        return top == 0;
    }

    /**
     * @brief Retorna el número de elementos en la pila.
     *
     * @return El tamaño actual de la pila.
     */
    int getSize() {
        return top;
    }

    /**
     * @brief Imprime el contenido de la pila.
     *
     * Muestra los elementos en el formato [ elemTop ... elemBottom ].
     */
    void print() {
        cout << "[ ";
        for (int i = top - 1; i >= 0; i--)
            cout << elements[i] << " ";
        cout << "]" << endl;
    }
};