/*
 * Archivo: Node.h
 * Descripción: Clase que representa un nodo en una lista enlazada simple.
 *              Almacena un elemento y un puntero al siguiente nodo.
 *
 * Autor(es): Profesor Mauricio Aviles Cisneros
 */

#pragma once

template <typename E>
class Node {
public:
    E element;                    ///< El elemento almacenado en el nodo.
    Node<E>* next;               ///< Puntero al siguiente nodo en la lista.

    /**
     * @brief Constructor que inicializa un nodo con un elemento y un puntero al siguiente nodo.
     *
     * @param element El elemento que se almacenará en el nodo.
     * @param next Puntero al siguiente nodo (opcional, por defecto es nullptr).
     */
    Node(E element, Node<E>* next = nullptr) {
        this->element = element;
        this->next = next;
    }

    /**
     * @brief Constructor que inicializa un nodo sin un elemento.
     *
     * @param next Puntero al siguiente nodo (opcional, por defecto es nullptr).
     */
    Node(Node<E>* next = nullptr) {
        this->next = next;
    }
};
