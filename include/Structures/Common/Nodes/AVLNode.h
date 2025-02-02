/**
 * @file AVLNode.h
 * @brief Clase que representa un nodo en un árbol AVL.
 *
 * Almacena un elemento, la altura del nodo y punteros a los nodos hijos izquierdo y derecho.
 *
 * @author Mauricio González Prendas
 */

#pragma once

#include <algorithm> // Para std::max

using std::max;

/**
 * @brief Clase que representa un nodo en un árbol AVL.
 *
 * Un nodo AVL almacena un elemento, la altura del nodo y punteros a sus hijos izquierdo y derecho.
 * Además, proporciona métodos para calcular el factor de balanceo, actualizar la altura y manejar
 * información sobre los hijos del nodo.
 *
 * @tparam E Tipo de los elementos almacenados en el nodo.
 */
template <typename E>
class AVLNode {
public:
    E element; ///< El elemento almacenado en el nodo.
    AVLNode<E>* left; ///< Puntero al hijo izquierdo del nodo.
    AVLNode<E>* right; ///< Puntero al hijo derecho del nodo.
    int height; ///< La altura del nodo.

    /**
     * @brief Constructor que inicializa un nodo con un elemento y una altura de 1.
     *
     * Los punteros a los hijos izquierdo y derecho se inicializan como nullptr.
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
     * Este valor se utiliza para determinar si el nodo está balanceado.
     *
     * @return El factor de balanceo del nodo (altura del hijo izquierdo - altura del hijo derecho).
     */
    int balanceFactor() {
        int leftHeight = (left == nullptr) ? 0 : left->height;
        int rightHeight = (right == nullptr) ? 0 : right->height;
        return leftHeight - rightHeight;
    }

    /**
     * @brief Actualiza la altura del nodo basándose en las alturas de los hijos.
     *
     * La altura del nodo es 1 más la mayor altura entre sus hijos izquierdo y derecho.
     */
    void updateHeight() {
        int leftHeight = (left == nullptr) ? 0 : left->height;
        int rightHeight = (right == nullptr) ? 0 : right->height;
        height = 1 + max(leftHeight, rightHeight);
    }

    /**
     * @brief Calcula el número de hijos del nodo.
     *
     * @return El número de hijos del nodo (0, 1 o 2).
     */
    int childrenCount() const {
        int count = 0;
        if (left != nullptr) count++;
        if (right != nullptr) count++;
        return count;
    }

    /**
     * @brief Retorna el único hijo del nodo si existe.
     *
     * Si el nodo tiene exactamente un hijo, retorna ese hijo. Si tiene 0 o 2 hijos, retorna nullptr.
     *
     * @return Puntero al único hijo del nodo, o nullptr si no hay un único hijo.
     */
    AVLNode<E>* onlyChild() const {
        if (left != nullptr && right == nullptr) return left;
        if (right != nullptr && left == nullptr) return right;
        return nullptr;
    }
};