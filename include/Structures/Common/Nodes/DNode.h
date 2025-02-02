/*
 * Archivo: DNode.h
 * Descripción: Clase que representa un nodo en una lista doblemente enlazada.
 *              Almacena un elemento y punteros a los nodos siguiente y anterior.
 *
 * Autor(es): Profesor Mauricio Aviles Cisneros
 */

#pragma once

template <typename E>
class DNode {
public:
    E element;                     ///< El elemento almacenado en el nodo.
    DNode<E>* next;               ///< Puntero al siguiente nodo en la lista.
    DNode<E>* previous;           ///< Puntero al nodo anterior en la lista.

    /**
     * @brief Constructor que inicializa un nodo con un elemento y punteros a nodos adyacentes.
     *
     * @param element El elemento que se almacenará en el nodo.
     * @param next Puntero al siguiente nodo.
     * @param previous Puntero al nodo anterior.
     */
    DNode(E element, DNode<E>* next, DNode<E>* previous) {
        this->element = element;
        this->next = next;
        this->previous = previous;
    }

    /**
     * @brief Constructor que inicializa un nodo sin elemento.
     *
     * @param next Puntero al siguiente nodo.
     * @param previous Puntero al nodo anterior.
     */
    DNode(DNode<E>* next, DNode<E>* previous) {
        this->next = next;
        this->previous = previous;
    }
};
