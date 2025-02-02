/*
 * Archivo: BSTree.h
 * Descripción: Implementación de un árbol binario de búsqueda (BST).
 *              El BST permite la inserción, búsqueda y eliminación de elementos
 *              de manera eficiente, manteniendo un orden específico.
 *
 * Autor(es): Profesor Mauricio Aviles Cisneros
 */

#pragma once

#include <stdexcept>
#include <iostream>
#include "Structures/Common/Nodes/BSTNode.h"
#include "Structures/Implementations/Lists/DLinkedList.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Clase que implementa un árbol binario de búsqueda (BST).
 * 
 * @tparam E Tipo de los elementos almacenados en el BST.
 */
template <typename E>
class BSTree {
private:
    // El árbol BST no permite la copia ni la asignación
    BSTree(const BSTree<E>& other) {}
    void operator=(const BSTree<E>& other) {}

    BSTNode<E>* root; ///< Puntero a la raíz del árbol.

    /**
     * @brief Función auxiliar para insertar un elemento en el árbol.
     * @param current Nodo actual en el recorrido del árbol.
     * @param element Elemento a insertar.
     * @return Puntero al nodo actualizado después de la inserción.
     * @throw runtime_error Si el elemento ya existe en el árbol.
     */
    BSTNode<E>* insertAux(BSTNode<E>* current, E element) {
        if (current == nullptr)
            return new BSTNode<E>(element);

        // Si se desea permitir elementos duplicados, eliminar este bloque
        if (element == current->element)
            throw runtime_error("Duplicated element.");

        if (element < current->element)
            current->left = insertAux(current->left, element);
        else
            current->right = insertAux(current->right, element);

        return current;
    }

    /**
     * @brief Función auxiliar para verificar si el árbol contiene un elemento.
     * @param current Nodo actual en el recorrido del árbol.
     * @param element Elemento a buscar.
     * @return true si el elemento se encuentra en el árbol, false en caso contrario.
     */
    bool containsAux(BSTNode<E>* current, E element) {
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
    E findAux(BSTNode<E>* current, E element) {
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
    BSTNode<E>* removeAux(BSTNode<E>* current, E element, E* result) {
        if (current == nullptr)
            throw runtime_error("Element not found.");

        if (element < current->element) {
            current->left = removeAux(current->left, element, result);
            return current;
        }
        if (element > current->element) {
            current->right = removeAux(current->right, element, result);
            return current;
        } else {
            *result = current->element;
            int childrenCount = current->childrenCount();
            if (childrenCount == 0) {
                delete current;
                return nullptr;
            }
            if (childrenCount == 1) {
                BSTNode<E>* child = current->onlyChild();
                delete current;
                return child;
            } else {
                BSTNode<E>* successor = findMin(current->right);
                swap(current, successor);
                current->right = removeAux(current->right, element, result);
                return current;
            }
        }
    }

    /**
     * @brief Encuentra el nodo con el valor mínimo en un subárbol.
     * @param current Nodo raíz del subárbol.
     * @return Puntero al nodo con el valor mínimo.
     */
    BSTNode<E>* findMin(BSTNode<E>* current) {
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    /**
     * @brief Intercambia los valores de dos nodos.
     * @param n1 Primer nodo.
     * @param n2 Segundo nodo.
     */
    void swap(BSTNode<E>* n1, BSTNode<E>* n2) {
        E temp = n1->element;
        n1->element = n2->element;
        n2->element = temp;
    }

    /**
     * @brief Función auxiliar para limpiar el árbol y liberar memoria.
     * @param current Nodo actual en el recorrido del árbol.
     */
    void clearAux(BSTNode<E>* current) {
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
    void getElementsAux(BSTNode<E>* current, List<E>* elements) {
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
    int getSizeAux(BSTNode<E>* current) {
        if (current == nullptr)
            return 0;
        return 1 + getSizeAux(current->left) + getSizeAux(current->right);
    }

    /**
     * @brief Calcula la altura de un subárbol.
     * @param current Nodo raíz del subárbol.
     * @return Altura del subárbol.
     */
    int height(BSTNode<E>* current) {
        if (current == nullptr)
            return 0;
        int lh = height(current->left);
        int rh = height(current->right);
        return 1 + (lh > rh ? lh : rh);
    }

public:
    /**
     * @brief Constructor por defecto que inicializa un árbol BST vacío.
     */
    BSTree() {
        root = nullptr;
    }

    /**
     * @brief Destructor que limpia el árbol y libera la memoria.
     */
    ~BSTree() {
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
     * @brief Imprime los elementos del árbol en orden.
     */
    void print() {
        List<E>* elements = getElements();
        elements->print();
        delete elements;
    }

    /**
     * @brief Obtiene la altura del árbol.
     * @return Altura del árbol.
     */
    int getHeight() {
        return height(root);
    }
};
