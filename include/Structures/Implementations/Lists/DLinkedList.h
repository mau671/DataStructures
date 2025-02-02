/**
 * @file DLinkedList.h
 * @brief Implementación de una lista doblemente enlazada utilizando nodos.
 * 
 * Proporciona operaciones de inserción, eliminación, búsqueda y manipulación de elementos.
 * 
 * @author Profesor Mauricio Aviles Cisneros
 * @author Mauricio González Prendas
 */

#pragma once

#include <stdexcept>
#include <iostream>
#include "Structures/Abstract/List.h"
#include "Structures/Common/Nodes/DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Clase que implementa una lista doblemente enlazada.
 * 
 * @tparam E Tipo de elementos almacenados en la lista.
 */
template <typename E>
class DLinkedList : public List<E> {
private:
    DNode<E>* head;    ///< Puntero al nodo ficticio al inicio de la lista.
    DNode<E>* tail;    ///< Puntero al nodo ficticio al final de la lista.
    DNode<E>* current; ///< Puntero al nodo actual.
    int size;          ///< Número de elementos en la lista.

public:
    /**
     * @brief Constructor que inicializa una lista vacía.
     */
    DLinkedList() {
        current = head = new DNode<E>(nullptr, nullptr);
        head->next = tail = new DNode<E>(nullptr, head);
        size = 0;
    }

    /**
     * @brief Destructor que limpia la lista y libera la memoria.
     */
    ~DLinkedList() {
        clear();
        delete head;
        delete tail;
    }

    /**
     * @brief Inserta un elemento en la posición actual.
     * 
     * @param element Elemento a insertar.
     */
    void insert(E element) {
        current->next = current->next->previous = new DNode<E>(element, current->next, current);
        size++;
    }

    /**
     * @brief Agrega un elemento al final de la lista.
     * 
     * @param element Elemento a agregar.
     */
    void append(E element) {
        tail->previous = tail->previous->next = new DNode<E>(element, tail, tail->previous);
        size++;
    }

    /**
     * @brief Reemplaza el elemento en la posición actual.
     * 
     * @param element Nuevo elemento.
     * @throw runtime_error Si la lista está vacía o no hay elemento actual.
     */
    void set(E element) {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->next == tail)
            throw runtime_error("No current element.");
        current->next->element = element;
    }

    /**
     * @brief Elimina y devuelve el elemento en la posición actual.
     * 
     * @return Elemento eliminado.
     * @throw runtime_error Si la lista está vacía o no hay elemento actual.
     */
    E remove() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->next == tail)
            throw runtime_error("No current element.");
        E result = current->next->element;
        current->next = current->next->next;
        delete current->next->previous;
        current->next->previous = current;
        size--;
        return result;
    }

    /**
     * @brief Devuelve el elemento en la posición actual.
     * 
     * @return Elemento en la posición actual.
     * @throw runtime_error Si la lista está vacía o no hay elemento actual.
     */
    E getElement() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->next == tail)
            throw runtime_error("No current element.");
        return current->next->element;
    }

    /**
     * @brief Elimina todos los elementos de la lista.
     */
    void clear() {
        while (head->next != tail) {
            head->next = head->next->next;
            delete head->next->previous;
        }
        current = tail->previous = head;
        size = 0;
    }

    /**
     * @brief Mueve el puntero actual al inicio de la lista.
     */
    void goToStart() {
        current = head;
    }

    /**
     * @brief Mueve el puntero actual al final de la lista.
     */
    void goToEnd() {
        current = tail->previous;
    }

    /**
     * @brief Mueve el puntero actual a una posición específica.
     * 
     * @param pos Posición a la que se moverá el puntero.
     * @throw runtime_error Si la posición está fuera de los límites de la lista.
     */
    void goToPos(int pos) {
        if (pos < 0 || pos > size)
            throw runtime_error("Index out of bounds.");
        if (pos <= size / 2) {
            current = head;
            for (int i = 0; i < pos; i++)
                current = current->next;
        } else {
            current = tail->previous;
            for (int i = 0; i < size - pos; i++)
                current = current->previous;
        }
    }

    /**
     * @brief Mueve el puntero actual al siguiente elemento.
     */
    void next() {
        if (current->next != tail)
            current = current->next;
    }

    /**
     * @brief Mueve el puntero actual al elemento anterior.
     */
    void previous() {
        if (current != head)
            current = current->previous;
    }

    /**
     * @brief Verifica si el puntero actual está al inicio de la lista.
     * 
     * @return true si está al inicio, false en caso contrario.
     */
    bool atStart() {
        return current == head;
    }

    /**
     * @brief Verifica si el puntero actual está al final de la lista.
     * 
     * @return true si está al final, false en caso contrario.
     */
    bool atEnd() {
        return current->next == tail;
    }

    /**
     * @brief Devuelve la posición actual del puntero en la lista.
     * 
     * @return Posición actual del puntero.
     */
    int getPos() {
        int pos = 0;
        DNode<E>* temp = head;
        while (temp != current) {
            temp = temp->next;
            pos++;
        }
        return pos;
    }

    /**
     * @brief Devuelve el número de elementos en la lista.
     * 
     * @return Tamaño de la lista.
     */
    int getSize() {
        return size;
    }

    /**
     * @brief Imprime los elementos de la lista.
     */
    void print() {
        cout << "[ ";
        DNode<E>* temp = head->next;
        while (temp != tail) {
            if (temp == current->next)
                cout << "*";
            cout << temp->element << " ";
            temp = temp->next;
        }
        if (current == tail->previous)
            cout << "*";
        cout << "]" << endl;
    }

    /**
     * @brief Devuelve el índice de un elemento en la lista, comenzando desde una posición específica.
     * 
     * @param element Elemento a buscar.
     * @param start Posición desde la que se inicia la búsqueda.
     * @return Índice del elemento, o -1 si no se encuentra.
     * @throw runtime_error Si la posición de inicio está fuera de los límites.
     */
    int indexOf(E element, int start = 0) {
        if (start < 0 || start >= size)
            throw runtime_error("Index out of bounds.");
        DNode<E>* temp = head->next;
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
     * @brief Verifica si la lista contiene un elemento específico.
     * 
     * @param element Elemento a buscar.
     * @return true si el elemento está en la lista, false en caso contrario.
     */
    bool contains(E element) {
        goToStart();
        while (!atEnd()) {
            if (element == getElement()) {
                return true;
            }
            next();
        }
        return false;
    }

    /**
     * @brief Compara si dos listas son iguales.
     * 
     * @param other Lista con la que se compara.
     * @return true si las listas son iguales, false en caso contrario.
     */
    bool equals(List<E>* other) {
        if (size != other->getSize())
            return false;
        DNode<E>* temp = head->next;
        for (int i = 0; i < size; i++) {
            if (temp->element != other->getElement())
                return false;
            temp = temp->next;
            other->next();
        }
        return true;
    }

    /**
     * @brief Invierte el orden de los elementos en la lista.
     */
    void reverse() {
        DNode<E>* temp = head;
        head = tail;
        tail = temp;
        current = head;
    }

    /**
     * @brief Extiende la lista actual con los elementos de otra lista.
     * 
     * @param other Lista cuyos elementos se agregarán.
     */
    void extend(List<E>* other) {
        goToEnd();
        for (int i = 0; i < other->getSize(); i++) {
            append(other->getElement());
            other->next();
        }
    }
};
