/**
 * @file DCircleList.h
 * @brief Implementación de una lista doblemente enlazada circular.
 * 
 * Proporciona operaciones de inserción, eliminación, búsqueda y manipulación de elementos.
 * 
 * @author Profesor Mauricio Aviles Cisneros
 * @author Mauricio González Prendas
 */

#pragma once

#include <stdexcept>
#include <iostream>
#include "Structures/Common/Nodes/DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Clase plantilla para una lista doblemente enlazada circular.
 *
 * Implementa una lista circular en la que cada nodo tiene enlaces tanto al siguiente
 * como al anterior, permitiendo la navegación bidireccional.
 *
 * @tparam E Tipo de dato almacenado en la lista.
 */
template <typename E>
class DCircleList {
private:
    DNode<E>* current; ///< Puntero al nodo actual de la lista.
    int size;          ///< Número de elementos en la lista.

public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa la lista vacía.
     */
    DCircleList() : current(nullptr), size(0) {}

    /**
     * @brief Destructor.
     *
     * Libera la memoria reservada eliminando todos los nodos de la lista.
     */
    ~DCircleList() {
        clear();
    }

    /**
     * @brief Inserta un elemento en la lista circular.
     *
     * Si la lista está vacía, crea el primer nodo y establece los enlaces
     * de siguiente y anterior apuntando a sí mismo. En caso contrario, inserta
     * el nuevo nodo inmediatamente después del nodo actual y ajusta los enlaces.
     *
     * @param element Elemento a insertar.
     */
    void insert(E element) {
        if (size == 0) {
            current = new DNode<E>(element);
            current->next = current;
            current->previous = current;
        } else {
            DNode<E>* newNode = new DNode<E>(element, current->next, current);
            current->next->previous = newNode;
            current->next = newNode;
        }
        size++;
    }

    /**
     * @brief Elimina y retorna el elemento ubicado después del nodo actual.
     *
     * Si la lista está vacía, lanza una excepción.
     *
     * @return El elemento eliminado.
     * @throws runtime_error Si la lista está vacía.
     */
    E remove() {
        if (size == 0)
            throw runtime_error("List is empty.");

        E result = current->next->element;
        DNode<E>* temp = current->next;

        if (size == 1) { // Si solo hay un elemento
            current = nullptr;
        } else {
            current->next = temp->next;
            temp->next->previous = current;
        }

        delete temp;
        size--;
        return result;
    }

    /**
     * @brief Elimina todos los elementos de la lista.
     *
     * Llama repetidamente a remove() hasta que la lista queda vacía.
     */
    void clear() {
        while (size > 0) {
            remove();
        }
    }

    /**
     * @brief Obtiene el primer elemento de la lista.
     *
     * @return El primer elemento de la lista.
     * @throws runtime_error Si la lista está vacía.
     */
    E getFront() const {
        if (size == 0)
            throw runtime_error("List is empty.");
        return current->next->element; // Primer elemento en la lista circular
    }

    /**
     * @brief Obtiene el último elemento de la lista.
     *
     * @return El último elemento de la lista.
     * @throws runtime_error Si la lista está vacía.
     */
    E getBack() const {
        if (size == 0)
            throw runtime_error("List is empty.");
        return current->element; // 'current' apunta al último elemento
    }

    /**
     * @brief Avanza al siguiente nodo de la lista.
     *
     * Actualiza el puntero current al siguiente nodo.
     * @throws runtime_error Si la lista está vacía.
     */
    void next() {
        if (size == 0)
            throw runtime_error("List is empty.");
        current = current->next;
    }

    /**
     * @brief Retrocede al nodo anterior de la lista.
     *
     * Actualiza el puntero current al nodo anterior.
     * @throws runtime_error Si la lista está vacía.
     */
    void previous() {
        if (size == 0)
            throw runtime_error("List is empty.");
        current = current->previous;
    }

    /**
     * @brief Retorna el número de elementos en la lista.
     *
     * @return El tamaño de la lista.
     */
    int getSize() const {
        return size;
    }

    /**
     * @brief Imprime los elementos de la lista.
     *
     * Muestra los elementos en el formato [ elem1 elem2 ... ].
     * Si la lista está vacía, imprime un mensaje indicándolo.
     */
    void print() const {
        if (size == 0) {
            cout << "List is empty." << endl;
            return;
        }

        DNode<E>* temp = current->next; // Comienza desde el frente
        cout << "[ ";
        for (int i = 0; i < size; i++) {
            cout << temp->element << " ";
            temp = temp->next;
        }
        cout << "]" << endl;
    }

    /**
     * @brief Compara dos listas circulares para determinar si son iguales.
     *
     * Dos listas se consideran iguales si tienen el mismo tamaño y sus elementos
     * en posiciones correspondientes son idénticos.
     *
     * @param other Puntero a la otra lista circular.
     * @return true si las listas son iguales, false en caso contrario.
     */
    bool equals(DCircleList<E>* other) const {
        if (size != other->getSize())
            return false;

        DNode<E>* temp1 = current->next;
        DNode<E>* temp2 = other->current->next;

        for (int i = 0; i < size; i++) {
            if (temp1->element != temp2->element)
                return false;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        return true;
    }

    /**
     * @brief Busca el índice de un elemento en la lista.
     *
     * La búsqueda comienza a partir del índice indicado.
     *
     * @param element Elemento a buscar.
     * @param start Índice desde el cual iniciar la búsqueda (por defecto 0).
     * @return El índice del elemento si se encuentra; de lo contrario, -1.
     * @throws runtime_error Si el índice inicial está fuera de los límites.
     */
    int indexOf(E element, int start = 0) const {
        if (start < 0 || start >= size)
            throw runtime_error("Index out of bounds.");

        DNode<E>* temp = current->next;
        for (int i = 0; i < start; i++)
            temp = temp->next;

        for (int i = start; i < size; i++) {
            if (temp->element == element)
                return i;
            temp = temp->next;
        }
        return -1;
    }

    /**
     * @brief Determina si la lista contiene un elemento específico.
     *
     * @param element Elemento a buscar.
     * @return true si el elemento está en la lista, false en caso contrario.
     */
    bool contains(E element) const {
        return indexOf(element, 0) != -1;
    }

    /**
     * @brief Invierte el orden de los elementos de la lista.
     *
     * Reorganiza los enlaces de los nodos para invertir el orden de la lista.
     * No se realiza ninguna acción si la lista tiene 0 o 1 elemento.
     */
    void reverse() {
        if (size <= 1)
            return;

        DNode<E>* temp = current->next;
        DNode<E>* prev = nullptr;
        for (int i = 0; i < size; i++) {
            DNode<E>* nextNode = temp->next;
            temp->next = prev;
            temp->previous = nextNode;
            prev = temp;
            temp = nextNode;
        }
        current->next = prev;
        prev->previous = current;
    }

    /**
     * @brief Extiende la lista agregando elementos de otra lista circular.
     *
     * Inserta todos los elementos de la lista "other" en la lista actual.
     *
     * @param other Puntero a la otra lista circular.
     */
    void extend(DCircleList<E>* other) {
        DNode<E>* temp = other->current->next;
        for (int i = 0; i < other->size; i++) {
            insert(temp->element);
            temp = temp->next;
        }
    }
};
