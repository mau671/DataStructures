/**
 * @file AVLTree.h
 * @brief Implementación de un árbol AVL, una estructura de datos de árbol binario de búsqueda autobalanceado.
 *
 * Garantiza operaciones eficientes de inserción, eliminación y búsqueda.
 *
 * @author Profesor Mauricio Aviles Cisneros
 * @author Mauricio González Prendas
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Structures/Common/Nodes/AVLNode.h"
#include "Structures/Implementations/Lists/DLinkedList.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Clase que implementa un árbol AVL.
 *
 * Un árbol AVL es un árbol binario de búsqueda autobalanceado que garantiza
 * que la diferencia de altura entre los subárboles izquierdo y derecho de cualquier nodo
 * sea como máximo 1. Esto asegura un rendimiento eficiente para operaciones de inserción,
 * eliminación y búsqueda.
 *
 * @tparam E Tipo de los elementos almacenados en el árbol AVL.
 */
template <typename E>
class AVLTree {
private:
    // El árbol AVL no permite copia ni asignación
    AVLTree(const AVLTree<E>& other) {}
    void operator=(const AVLTree<E>& other) {}

    AVLNode<E>* root; ///< Puntero a la raíz del árbol AVL.
    int rotationCount; ///< Contador de las rotaciones realizadas para mantener el balance.

    /**
     * @brief Función auxiliar para insertar un elemento en el árbol.
     * @param current Nodo actual en el recorrido del árbol.
     * @param element Elemento a insertar.
     * @return Puntero al nodo actualizado después de la inserción.
     * @throw runtime_error Si el elemento ya existe en el árbol.
     */
    AVLNode<E>* insertAux(AVLNode<E>* current, E element) {
        if (current == nullptr)
            return new AVLNode<E>(element);

        if (element == current->element)
            throw runtime_error("Duplicated element.");

        if (element < current->element) {
            current->left = insertAux(current->left, element);
        } else {
            current->right = insertAux(current->right, element);
        }

        current->updateHeight();
        return rebalance(current);
    }

    /**
     * @brief Función auxiliar para verificar si el árbol contiene un elemento.
     * @param current Nodo actual en el recorrido del árbol.
     * @param element Elemento a buscar.
     * @return true si el elemento se encuentra, false en caso contrario.
     */
    bool containsAux(AVLNode<E>* current, E element) {
        if (current == nullptr)
            return false;
        if (element == current->element)
            return true;
        if (element < current->element)
            return containsAux(current->left, element);
        else
            return containsAux(current->right, element);
    }

    /**
     * @brief Función auxiliar para encontrar un elemento en el árbol.
     * @param current Nodo actual en el recorrido del árbol.
     * @param element Elemento a buscar.
     * @return El elemento encontrado.
     * @throw runtime_error Si el elemento no se encuentra en el árbol.
     */
    E findAux(AVLNode<E>* current, E element) {
        if (current == nullptr)
            throw runtime_error("Element not found.");
        if (element == current->element)
            return current->element;
        if (element < current->element)
            return findAux(current->left, element);
        else
            return findAux(current->right, element);
    }

    /**
     * @brief Función auxiliar para eliminar un elemento del árbol.
     * @param current Nodo actual en el recorrido del árbol.
     * @param element Elemento a eliminar.
     * @param result Puntero para almacenar el elemento eliminado.
     * @return Puntero al nodo actualizado después de la eliminación.
     * @throw runtime_error Si el elemento no se encuentra en el árbol.
     */
    AVLNode<E>* removeAux(AVLNode<E>* current, E element, E* result) {
        if (current == nullptr)
            throw runtime_error("Element not found.");

        if (element < current->element) {
            current->left = removeAux(current->left, element, result);
        } else if (element > current->element) {
            current->right = removeAux(current->right, element, result);
        } else {
            *result = current->element;
            int childrenCount = current->childrenCount();
            if (childrenCount == 0) {
                delete current;
                return nullptr;
            }
            if (childrenCount == 1) {
                AVLNode<E>* child = current->onlyChild();
                delete current;
                return child;
            } else {
                AVLNode<E>* successor = findMin(current->right);
                swap(current, successor);
                current->right = removeAux(current->right, element, result);
            }
        }

        current->updateHeight();
        return rebalance(current);
    }

    /**
     * @brief Encuentra el nodo con el valor mínimo en un subárbol.
     * @param current Nodo raíz del subárbol.
     * @return Puntero al nodo con el valor mínimo.
     */
    AVLNode<E>* findMin(AVLNode<E>* current) {
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    /**
     * @brief Intercambia los valores de dos nodos.
     * @param n1 Primer nodo.
     * @param n2 Segundo nodo.
     */
    void swap(AVLNode<E>* n1, AVLNode<E>* n2) {
        E temp = n1->element;
        n1->element = n2->element;
        n2->element = temp;
    }

    /**
     * @brief Función auxiliar para limpiar el árbol y liberar memoria.
     * @param current Nodo actual en el recorrido del árbol.
     */
    void clearAux(AVLNode<E>* current) {
        if (current == nullptr)
            return;
        clearAux(current->left);
        clearAux(current->right);
        delete current;
    }

    /**
     * @brief Función auxiliar para obtener todos los elementos del árbol en orden.
     * @param current Nodo actual en el recorrido del árbol.
     * @param elements Lista donde se almacenarán los elementos.
     */
    void getElementsAux(AVLNode<E>* current, List<E>* elements) {
        if (current == nullptr)
            return;
        getElementsAux(current->left, elements);
        elements->append(current->element);
        getElementsAux(current->right, elements);
    }

    /**
     * @brief Función auxiliar para calcular el tamaño del árbol.
     * @param current Nodo actual en el recorrido del árbol.
     * @return Número de nodos en el subárbol.
     */
    int getSizeAux(AVLNode<E>* current) {
        if (current == nullptr)
            return 0;
        return 1 + getSizeAux(current->left) + getSizeAux(current->right);
    }

    /**
     * @brief Realiza una rotación hacia la derecha en un nodo.
     * @param current Nodo sobre el cual se realizará la rotación.
     * @return Puntero al nodo actualizado después de la rotación.
     */
    AVLNode<E>* rotateRight(AVLNode<E>* current) {
        AVLNode<E>* temp = current->left;
        current->left = temp->right;
        temp->right = current;
        current->updateHeight();
        temp->updateHeight();
        rotationCount++;
        return temp;
    }

    /**
     * @brief Realiza una rotación hacia la izquierda en un nodo.
     * @param current Nodo sobre el cual se realizará la rotación.
     * @return Puntero al nodo actualizado después de la rotación.
     */
    AVLNode<E>* rotateLeft(AVLNode<E>* current) {
        AVLNode<E>* temp = current->right;
        current->right = temp->left;
        temp->left = current;
        current->updateHeight();
        temp->updateHeight();
        rotationCount++;
        return temp;
    }

    /**
     * @brief Rebalancea el subárbol si está desbalanceado.
     * @param current Nodo raíz del subárbol.
     * @return Puntero al nodo actualizado después del rebalanceo.
     */
    AVLNode<E>* rebalance(AVLNode<E>* current) {
        int balance = current->balanceFactor();
        if (balance > 1) {
            if (current->left->balanceFactor() < 0)
                current->left = rotateLeft(current->left);
            return rotateRight(current);
        }
        if (balance < -1) {
            if (current->right->balanceFactor() > 0)
                current->right = rotateRight(current->right);
            return rotateLeft(current);
        }
        return current;
    }

public:
    /**
     * @brief Constructor por defecto que inicializa un árbol AVL vacío.
     */
    AVLTree() {
        root = nullptr;
        rotationCount = 0;
    }

    /**
     * @brief Destructor que limpia el árbol y libera la memoria.
     */
    ~AVLTree() {
        clear();
    }

    /**
     * @brief Inserta un elemento en el árbol.
     * @param element Elemento a insertar.
     */
    void insert(E element) {
        root = insertAux(root, element);
    }

    /**
     * @brief Verifica si el árbol contiene un elemento.
     * @param element Elemento a buscar.
     * @return true si el elemento se encuentra en el árbol, false en caso contrario.
     */
    bool contains(E element) {
        return containsAux(root, element);
    }

    /**
     * @brief Encuentra un elemento en el árbol.
     * @param element Elemento a buscar.
     * @return El elemento encontrado.
     * @throw runtime_error Si el elemento no se encuentra en el árbol.
     */
    E find(E element) {
        return findAux(root, element);
    }

    /**
     * @brief Elimina un elemento del árbol.
     * @param element Elemento a eliminar.
     * @return El elemento eliminado.
     * @throw runtime_error Si el elemento no se encuentra en el árbol.
     */
    E remove(E element) {
        E result;
        root = removeAux(root, element, &result);
        return result;
    }

    /**
     * @brief Limpia el árbol y libera la memoria.
     */
    void clear() {
        clearAux(root);
        root = nullptr;
    }

    /**
     * @brief Obtiene todos los elementos del árbol en orden.
     * @return Lista de elementos en orden.
     */
    List<E>* getElements() {
        List<E>* elements = new DLinkedList<E>();
        getElementsAux(root, elements);
        return elements;
    }

    /**
     * @brief Obtiene el tamaño del árbol.
     * @return Número de elementos en el árbol.
     */
    int getSize() {
        return getSizeAux(root);
    }

    /**
     * @brief Obtiene la altura del árbol.
     * @return Altura del árbol.
     */
    int getHeight() {
        return (root == nullptr) ? 0 : root->height;
    }

    /**
     * @brief Obtiene el número de rotaciones realizadas.
     * @return Número de rotaciones.
     */
    int getRotationCount() const {
        return rotationCount;
    }

    /**
     * @brief Imprime el contenido del árbol en orden.
     */
    void print() {
        List<E>* elements = getElements();
        elements->print();
        delete elements;
    }
};
