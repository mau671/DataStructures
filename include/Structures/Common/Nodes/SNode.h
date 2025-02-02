/*
 * Archivo: SNode.h
 * Descripción: Clase que representa un nodo en un �rbol binario con enlaces a sus hijos y su padre,
 *              permite almacenar un elemento de tipo E y enlazarlo con sus hijos y su padre.
 * 
 * Autor: Profesor Mauricio Aviles Cisneros
 */

#pragma once

/**
 * @brief Clase que representa un nodo en un �rbol binario con enlaces a sus hijos y su padre.
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
     * @param element El elemento a almacenar en el nodo.
     */
    SNode(E element) {
        this->element = element;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    /**
     * @brief Calcula el n�mero de hijos no nulos del nodo.
     *
     * @return El n�mero de hijos (0, 1 o 2).
     */
    int childrenCount() {
        return (left == nullptr ? 0 : 1) + (right == nullptr ? 0 : 1);
    }

    /**
     * @brief Obtiene el �nico hijo del nodo si tiene exactamente uno.
     *
     * @return Puntero al �nico hijo, o nullptr si el nodo no tiene o tiene dos hijos.
     */
    SNode<E>* getUniqueChild() {
        return (left == nullptr ? right : left);
    }
};
