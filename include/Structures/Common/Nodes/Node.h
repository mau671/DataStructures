/**
 * @file Node.h
 * @brief Clase que representa un nodo en una lista enlazada simple.
 *
 * Almacena un elemento y un puntero al siguiente nodo.
 *
 * @author Profesor Mauricio Aviles Cisneros
 */

#pragma once

/**
 * @brief Clase que representa un nodo en una lista enlazada simple.
 *
 * Un nodo en una lista enlazada simple almacena un elemento y un puntero
 * al siguiente nodo. Proporciona constructores para inicializar el nodo
 * con o sin un elemento.
 *
 * @tparam E Tipo de los elementos almacenados en el nodo.
 */
template <typename E>
class Node {
public:
    E element; ///< El elemento almacenado en el nodo.
    Node<E>* next; ///< Puntero al siguiente nodo en la lista.

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
     * Este constructor es útil para nodos centinelas o nodos temporales.
     *
     * @param next Puntero al siguiente nodo (opcional, por defecto es nullptr).
     */
    Node(Node<E>* next = nullptr) {
        this->next = next;
    }
};