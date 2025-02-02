/**
 * @file SNode.h
 * @brief Clase que representa un nodo en un árbol binario con enlaces a sus hijos y su padre.
 *
 * Permite almacenar un elemento de tipo E y enlazarlo con sus hijos y su padre.
 *
 * @author Profesor Mauricio Aviles Cisneros
 */

#pragma once

/**
 * @brief Clase que representa un nodo en un árbol binario con enlaces a sus hijos y su padre.
 *
 * Un nodo en este árbol almacena un elemento, punteros a sus hijos izquierdo y derecho,
 * y un puntero a su nodo padre. Además, proporciona métodos para calcular el número de hijos
 * y obtener el único hijo si existe.
 *
 * @tparam E Tipo de dato almacenado en el nodo.
 */
template <typename E>
class SNode {
public:
    SNode<E>* left;   ///< Puntero al nodo hijo izquierdo.
    SNode<E>* right;  ///< Puntero al nodo hijo derecho.
    SNode<E>* parent; ///< Puntero al nodo padre.
    E element;        ///< Elemento almacenado en el nodo.

    /**
     * @brief Constructor que inicializa un nodo con un elemento dado y sin hijos ni padre.
     *
     * Los punteros a los hijos izquierdo, derecho y padre se inicializan como nullptr.
     *
     * @param element El elemento a almacenar en el nodo.
     */
    SNode(E element) {
        this->element = element;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    /**
     * @brief Calcula el número de hijos no nulos del nodo.
     *
     * @return El número de hijos (0, 1 o 2).
     */
    int childrenCount() {
        return (left == nullptr ? 0 : 1) + (right == nullptr ? 0 : 1);
    }

    /**
     * @brief Obtiene el único hijo del nodo si tiene exactamente uno.
     *
     * Si el nodo tiene exactamente un hijo (izquierdo o derecho), retorna ese hijo.
     * Si el nodo no tiene hijos o tiene dos hijos, retorna nullptr.
     *
     * @return Puntero al único hijo, o nullptr si el nodo no tiene o tiene dos hijos.
     */
    SNode<E>* getUniqueChild() {
        return (left == nullptr ? right : left);
    }
};