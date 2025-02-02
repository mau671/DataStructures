/* 
 * Archivo: SplayTree.h
 * Descripción: Clase que implementa un árbol Splay, una estructura de datos autoajustable que
 *              mueve los elementos recientemente accedidos a la raíz mediante operaciones de rotaci�n.
 * 
 * Autor: Profesor Mauricio Aviles Cisneros
 */

#pragma once

#include <stdexcept>
#include <iostream>
#include "Structures/Common/Nodes/SNode.h"
#include "Structures/Implementations/Lists/DLinkedList.h"

using std::cout;
using std::endl;
using std::runtime_error;

/**
 * @brief Clase que implementa un árbol Splay, una estructura de datos autoajustable que
 *        mueve los elementos recientemente accedidos a la raíz mediante operaciones de rotación.
 *
 * @tparam E Tipo de los elementos almacenados en el árbol.
 */
template <typename E>
class SplayTree {
private:
    SNode<E>* root; ///< Nodo raíz del árbol Splay.
    SNode<E>* last; ///< Último nodo accedido (para la Operación de splay).

    /**
     * @brief Función auxiliar para insertar un elemento en el árbol.
     *
     * @param current Nodo actual en el que se intenta insertar el elemento.
     * @param element Elemento a insertar.
     * @return Nodo raíz después de la inserción.
     * @throw runtime_error si el elemento ya existe en el árbol.
     */
    SNode<E>* insertAux(SNode<E>* current, E element) {
        if (current == nullptr) {
            SNode<E>* result = new SNode<E>(element);
            last = result;
            return result;
        }
        if (element == current->element) {
            last = current;
            throw runtime_error("Duplicated element.");
        }
        if (element < current->element) {
            current->left = insertAux(current->left, element);
            current->left->parent = current;
            return current;
        }
        else {
            current->right = insertAux(current->right, element);
            current->right->parent = current;
            return current;
        }
    }

    /**
     * @brief Función auxiliar para encontrar un elemento en el árbol.
     *
     * @param current Nodo actual donde se busca el elemento.
     * @param element Elemento a buscar.
     * @return El elemento encontrado.
     * @throw runtime_error si el elemento no existe en el árbol.
     */
    E findAux(SNode<E>* current, E element) {
        if (current == nullptr)
            throw runtime_error("Element not found.");
        last = current;
        if (element == current->element) {
            return current->element;
        }
        if (element < current->element)
            return findAux(current->left, element);
        else
            return findAux(current->right, element);
    }

    /**
     * @brief Función auxiliar para obtener un puntero a un elemento en el árbol.
     *
     * @param current Nodo actual donde se busca el elemento.
     * @param element Elemento a buscar.
     * @return Puntero al elemento encontrado.
     * @throw runtime_error si el elemento no existe en el árbol.
     */
    E* findPointerAux(SNode<E>* current, E element) {
        if (current == nullptr)
            throw runtime_error("Element not found.");
        last = current;
        if (element == current->element)
            return &(current->element);
        if (element < current->element)
            return findPointerAux(current->left, element);
        else
            return findPointerAux(current->right, element);
    }

    /**
     * @brief Función auxiliar para verificar si un elemento existe en el árbol.
     *
     * @param current Nodo actual donde se busca el elemento.
     * @param element Elemento a buscar.
     * @return true si el elemento existe, false en caso contrario.
     */
    bool containsAux(SNode<E>* current, E element) {
        if (current == nullptr)
            return false;
        last = current;
        if (element == current->element)
            return true;
        if (element < current->element)
            return containsAux(current->left, element);
        else
            return containsAux(current->right, element);
    }

    /**
     * @brief Función auxiliar para eliminar un elemento del árbol.
     *
     * @param current Nodo actual donde se intenta eliminar el elemento.
     * @param element Elemento a eliminar.
     * @param result Puntero donde se almacenará el valor del elemento eliminado.
     * @return Nodo raíz después de la eliminación.
     * @throw runtime_error si el elemento no existe en el árbol.
     */
    SNode<E>* removeAux(SNode<E>* current, E element, E* result) {
        if (current == nullptr)
            throw runtime_error("Element not found.");
        if (element < current->element) {
            last = current;
            current->left = removeAux(current->left, element, result);
            if (current->left != nullptr)
                current->left->parent = current;
            return current;
        }
        if (element > current->element) {
            last = current;
            current->right = removeAux(current->right, element, result);
            if (current->right != nullptr)
                current->right->parent = current;
            return current;
        }
        else {
            last = current->parent;
            *result = current->element;
            if (current->childrenCount() == 0) {
                delete current;
                return nullptr;
            }
            if (current->childrenCount() == 1) {
                SNode<E>* child = current->getUniqueChild();
                child->parent = current->parent;
                delete current;
                return child;
            }
            else {
                SNode<E>* successor = getSuccessor(current);
                swap(current, successor);
                current->right = removeAux(current->right, element, result);
                if (current->right != nullptr)
                    current->right->parent = current;
                return current;
            }
        }
    }

    /**
     * @brief Función auxiliar para encontrar el sucesor de un nodo.
     *
     * @param current Nodo actual cuyo sucesor se busca.
     * @return Puntero al nodo sucesor.
     */
    SNode<E>* getSuccessor(SNode<E>* current) {
        SNode<E>* successor = current->right;
        while (successor->left != nullptr)
            successor = successor->left;
        return successor;
    }

    /**
     * @brief Intercambia los valores de dos nodos.
     *
     * @param n1 Primer nodo.
     * @param n2 Segundo nodo.
     */
    void swap(SNode<E>* n1, SNode<E>* n2) {
        E temp = n1->element;
        n1->element = n2->element;
        n2->element = temp;
    }

    /**
     * @brief Función auxiliar para limpiar (eliminar) todos los nodos del árbol.
     *
     * @param current Nodo actual a limpiar.
     */
    void clearAux(SNode<E>* current) {
        if (current == nullptr)
            return;
        clearAux(current->left);
        clearAux(current->right);
        delete current;
    }

    /**
     * @brief Función auxiliar para obtener todos los elementos del árbol en orden.
     *
     * @param current Nodo actual a procesar.
     * @param elements Lista donde se almacenarán los elementos.
     */
    void getElementsAux(SNode<E>* current, List<E>* elements) {
        if (current == nullptr)
            return;
        getElementsAux(current->left, elements);
        elements->append(current->element);
        getElementsAux(current->right, elements);
    }

    /**
     * @brief Función auxiliar para contar el número de nodos en el árbol.
     *
     * @param current Nodo actual a contar.
     * @return Número de nodos en el árbol.
     */
    int getSizeAux(SNode<E>* current) {
        if (current == nullptr)
            return 0;
        return 1 + getSizeAux(current->left) + getSizeAux(current->right);
    }

    /**
     * @brief Función auxiliar para calcular la altura del árbol.
     *
     * @param current Nodo actual.
     * @return Altura del árbol.
     */
    int height(SNode<E>* current) {
        if (current == nullptr)
            return 0;
        int lh = height(current->left);
        int rh = height(current->right);
        return 1 + (lh > rh ? lh : rh);
    }

    /**
     * @brief Realiza una rotación a la derecha en el nodo especificado.
     *
     * @param current Nodo en el que se realiza la rotación.
     * @throw runtime_error si no es posible rotar.
     */
    void rotateRight(SNode<E>* current) {
        if (current == nullptr || current->left == nullptr)
            throw runtime_error("Can't rotate right.");
        SNode<E>* temp = current->left;
        temp->parent = current->parent;
        current->left = temp->right;
        if (current->left != nullptr)
            current->left->parent = current;
        temp->right = current;
        current->parent = temp;
        if (current == root)
            root = temp;
        else if (temp->parent->right == current)
            temp->parent->right = temp;
        else
            temp->parent->left = temp;
    }

    /**
     * @brief Realiza una rotación a la izquierda en el nodo especificado.
     *
     * @param current Nodo en el que se realiza la rotación.
     * @throw runtime_error si no es posible rotar.
     */
    void rotateLeft(SNode<E>* current) {
        if (current == nullptr || current->right == nullptr)
            throw runtime_error("Can't rotate left.");
        SNode<E>* temp = current->right;
        temp->parent = current->parent;
        current->right = temp->left;
        if (current->right != nullptr)
            current->right->parent = current;
        temp->left = current;
        current->parent = temp;
        if (current == root)
            root = temp;
        else if (temp->parent->right == current)
            temp->parent->right = temp;
        else
            temp->parent->left = temp;
    }

    /**
     * @brief Operación de splay que mueve el último nodo accedido a la raíz.
     */
    void splay() {
        if (last == nullptr)
            return;
        SNode<E>* current = last;
        while (last != root) {
            if (current == root->left) {
                rotateRight(root);
                root->parent = nullptr;
            }
            else if (current == root->right) {
                rotateLeft(root);
                root->parent = nullptr;
            }
            else {
                SNode<E>* grand = current->parent->parent;
                if (grand->left != nullptr && grand->left->left == current) {
                    rotateRight(grand);
                    rotateRight(current->parent);
                }
                else if (grand->right != nullptr && grand->right->right == current) {
                    rotateLeft(grand);
                    rotateLeft(current->parent);
                }
                else if (grand->left != nullptr && grand->left->right == current) {
                    rotateLeft(current->parent);
                    rotateRight(grand);
                }
                else {
                    rotateRight(current->parent);
                    rotateLeft(grand);
                }
            }
        }
    }

public:
    /**
     * @brief Constructor por defecto. Inicializa un árbol Splay vacío.
     */
    SplayTree() {
        root = nullptr;
        last = nullptr;
    }

    /**
     * @brief Destructor. Libera todos los recursos utilizados.
     */
    ~SplayTree() {
        clear();
    }

    /**
     * @brief Inserta un elemento en el árbol.
     *
     * @param element Elemento a insertar.
     * @throw runtime_error si el elemento ya existe.
     */
    void insert(E element) {
        try {
            root = insertAux(root, element);
            root->parent = nullptr;
            splay();
        }
        catch (runtime_error& e) {
            splay();
            throw e;
        }
    }

    /**
     * @brief Busca un elemento en el árbol.
     *
     * @param element Elemento a buscar.
     * @return El elemento encontrado.
     * @throw runtime_error si el elemento no existe.
     */
    E find(E element) {
        try {
            E result = findAux(root, element);
            splay();
            return result;
        }
        catch (runtime_error& e) {
            splay();
            throw e;
        }
    }

    /**
     * @brief Busca un puntero al elemento en el árbol.
     *
     * @param element Elemento a buscar.
     * @return Puntero al elemento encontrado.
     * @throw runtime_error si el elemento no existe.
     */
    E* findPointer(E element) {
        try {
            E* result = findPointerAux(root, element);
            splay();
            return result;
        }
        catch (runtime_error& e) {
            splay();
            throw e;
        }
    }

    /**
     * @brief Verifica si el árbol contiene un elemento.
     *
     * @param element Elemento a verificar.
     * @return true si el elemento existe, false en caso contrario.
     */
    bool contains(E element) {
        bool result = containsAux(root, element);
        splay();
        return result;
    }

    /**
     * @brief Elimina un elemento del árbol.
     *
     * @param element Elemento a eliminar.
     * @return El valor del elemento eliminado.
     * @throw runtime_error si el elemento no existe.
     */
    E remove(E element) {
        try {
            E result;
            root = removeAux(root, element, &result);
            if (root != nullptr) root->parent = nullptr;
            splay();
            return result;
        }
        catch (runtime_error& e) {
            splay();
            throw e;
        }
    }

    /**
     * @brief Limpia el árbol, eliminando todos sus elementos.
     */
    void clear() {
        clearAux(root);
        last = root = nullptr;
    }

    /**
     * @brief Obtiene una lista de todos los elementos del árbol en orden.
     *
     * @return Puntero a una lista con los elementos en orden.
     */
    List<E>* getElements() {
        List<E>* elements = new DLinkedList<E>();
        getElementsAux(root, elements);
        return elements;
    }

    /**
     * @brief Retorna el tama�o del árbol (número de nodos).
     *
     * @return Tama�o del árbol.
     */
    int getSize() {
        return getSizeAux(root);
    }

    /**
     * @brief Retorna la altura del árbol.
     *
     * @return Altura del árbol.
     */
    int getHeight() {
        return height(root);
    }

    /**
     * @brief Imprime todos los elementos del árbol.
     */
    void print() {
        List<E>* elements = getElements();
        elements->print();
        delete elements;
    }
};

