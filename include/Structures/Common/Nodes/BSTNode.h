/*
 * Archivo: BSTNode.h
 * Descripción: Clase que representa un nodo en un árbol de búsqueda binaria (BST).
 *              Almacena un elemento y punteros a los nodos hijos izquierdo y derecho.
 *
 * Autor(es): Profesor Mauricio Aviles Cisneros
 */

#pragma once

template <typename E>
class BSTNode {
public:
    E element;                     ///< El elemento almacenado en el nodo.
    BSTNode<E>* left;             ///< Puntero al hijo izquierdo del nodo.
    BSTNode<E>* right;            ///< Puntero al hijo derecho del nodo.

    /**
     * @brief Constructor que inicializa un nodo con un elemento.
     *
     * @param element El elemento que se almacenará en el nodo.
     */
    BSTNode(E element) {
        this->element = element;
        left = nullptr;
        right = nullptr;
    }

    /**
     * @brief Verifica si el nodo es una hoja.
     *
     * Un nodo es considerado una hoja si no tiene hijos.
     *
     * @return true si el nodo es una hoja, false en caso contrario.
     */
    bool isLeaf() {
        return left == nullptr && right == nullptr;
    }

    /**
     * @brief Cuenta el número de hijos del nodo.
     *
     * @return El número de hijos (0, 1 o 2).
     */
    int childrenCount() {
        return (left == nullptr ? 0 : 1) + (right == nullptr ? 0 : 1);
    }

    /**
     * @brief Devuelve el único hijo del nodo si existe.
     *
     * Si el nodo tiene un solo hijo, se retorna ese hijo.
     *
     * @return Un puntero al único hijo del nodo, o nullptr si no tiene hijos.
     */
    BSTNode<E>* onlyChild() {
        return left == nullptr ? right : left;
    }
};
