/**
 * @file DNode.h
 * @brief Clase que representa un nodo en una lista doblemente enlazada.
 *
 * Almacena un elemento y punteros a los nodos siguiente y anterior.
 *
 * @author Profesor Mauricio Aviles Cisneros
 */

#pragma once

/**
 * @brief Clase que representa un nodo en una lista doblemente enlazada.
 *
 * Un nodo en una lista doblemente enlazada almacena un elemento y punteros
 * a los nodos adyacentes (siguiente y anterior). Proporciona constructores
 * para inicializar el nodo con o sin un elemento.
 *
 * @tparam E Tipo de los elementos almacenados en el nodo.
 */
template <typename E>
class DNode {
public:
    E element; ///< El elemento almacenado en el nodo.
    DNode<E>* next; ///< Puntero al siguiente nodo en la lista.
    DNode<E>* previous; ///< Puntero al nodo anterior en la lista.

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
     * Este constructor es útil para nodos centinelas o nodos temporales.
     *
     * @param next Puntero al siguiente nodo.
     * @param previous Puntero al nodo anterior.
     */
    DNode(DNode<E>* next, DNode<E>* previous) {
        this->next = next;
        this->previous = previous;
    }
};