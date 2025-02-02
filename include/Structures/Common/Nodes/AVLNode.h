/*
 * Archivo: AVLNode.h
 * Descripción: Clase que representa un nodo en un árbol AVL.
 *              Almacena un elemento, la altura del nodo y punteros a los nodos hijos izquierdo y derecho.
 *
 * Autor(es): Mauricio González Prendas
 */

using std::max;

#pragma once

template <typename E>
class AVLNode {
public:
    E element;                    ///< El elemento almacenado en el nodo.
    AVLNode<E>* left;             ///< Puntero al hijo izquierdo del nodo.
    AVLNode<E>* right;            ///< Puntero al hijo derecho del nodo.
    int height;                   ///< La altura del nodo.

    /**
     * @brief Constructor que inicializa un nodo con un elemento y una altura de 1.
     *
     * @param element El elemento que se almacenará en el nodo.
     */
    AVLNode(E element) {
        this->element = element;
        left = nullptr;
        right = nullptr;
        height = 1;
    }

    /**
     * @brief Calcula la diferencia de altura entre los hijos izquierdo y derecho.
     *
     * @return El factor de balanceo del nodo.
     */
    int balanceFactor() {
        int leftHeight = (left == nullptr) ? 0 : left->height;
        int rightHeight = (right == nullptr) ? 0 : right->height;
        return leftHeight - rightHeight;
    }

    /**
     * @brief Actualiza la altura del nodo basándose en las alturas de los hijos.
     */
    void updateHeight() {
        int leftHeight = (left == nullptr) ? 0 : left->height;
        int rightHeight = (right == nullptr) ? 0 : right->height;
        height = 1 + max(leftHeight, rightHeight);
    }

    int childrenCount() const {
        int count = 0;
        if (left != nullptr) count++;
        if (right != nullptr) count++;
        return count;
    }

    AVLNode<E>* onlyChild() const {
        if (left != nullptr && right == nullptr) return left;
        if (right != nullptr && left == nullptr) return right;
        return nullptr;
    }

};
