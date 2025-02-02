/*
 * Archivo: CircleList.h
 * Descripción: Implementación de una lista circular utilizando nodos enlazados.
 *              Proporciona operaciones de inserción, eliminación, búsqueda y
 *              manipulación de elementos.
 *
 * Autor(es): Profesor Mauricio Aviles Cisneros, Mauricio González Prendas
 */

#pragma once

#include <stdexcept>
#include <iostream>
#include "Structures/Common/Nodes/Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Clase plantilla para una lista circular.
 *
 * Esta clase implementa una lista circular genérica que permite insertar,
 * eliminar, navegar y manipular elementos de forma circular.
 *
 * @tparam E Tipo de dato almacenado en la lista.
 */
template <typename E>
class CircleList {
private:
    Node<E>* current; ///< Puntero al nodo actual de la lista.
    int size;         ///< Número de elementos en la lista.

public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa la lista circular vacía.
     */
    CircleList() : current(nullptr), size(0) {}

    /**
     * @brief Destructor.
     *
     * Libera la memoria reservada y elimina todos los nodos de la lista.
     */
    ~CircleList() {
        clear();
    }

    /**
     * @brief Inserta un elemento en la lista circular.
     *
     * Si la lista está vacía, crea el primer nodo y establece el enlace circular.
     * En caso contrario, inserta el nuevo elemento inmediatamente después del nodo actual.
     *
     * @param element Elemento a insertar en la lista.
     */
    void insert(E element) {
        if (size == 0) {
            current = new Node<E>(element);
            current->next = current;
        }
        else {
            Node<E>* newNode = new Node<E>(element, current->next);
            current->next = newNode;
        }
        size++;
    }

    /**
     * @brief Elimina y retorna el elemento que está después del nodo actual.
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
        Node<E>* temp = current->next;

        if (size == 1) { // Si solo hay un elemento
            current = nullptr;
        } else {
            current->next = temp->next;
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
    E getFront() {
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
    E getBack() {
        if (size == 0)
            throw runtime_error("List is empty.");
        return current->element; // current apunta al último elemento
    }

    /**
     * @brief Avanza al siguiente elemento de la lista.
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
     * @brief Retrocede al nodo anterior en la lista.
     *
     * Recorre la lista hasta encontrar el nodo que precede al actual.
     * @throws runtime_error Si la lista está vacía.
     */
    void previous() {
        if (size == 0)
            throw runtime_error("List is empty.");

        Node<E>* temp = current;
        while (temp->next != current) { // Buscar el nodo anterior
            temp = temp->next;
        }
        current = temp;
    }

    /**
     * @brief Retorna el número de elementos en la lista.
     *
     * @return Tamaño de la lista.
     */
    int getSize() {
        return size;
    }

    /**
     * @brief Imprime el contenido de la lista.
     *
     * Muestra todos los elementos de la lista en formato [ elem1 elem2 ... ].
     * Si la lista está vacía, imprime un mensaje indicándolo.
     */
    void print() {
        if (size == 0) {
            cout << "List is empty." << endl;
            return;
        }

        Node<E>* temp = current->next; // Comenzar desde el frente
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
     * Dos listas se consideran iguales si tienen el mismo tamaño y los elementos en
     * las mismas posiciones son idénticos.
     *
     * @param other Puntero a otra lista circular a comparar.
     * @return true si las listas son iguales, false en caso contrario.
     */
    bool equals(CircleList<E>* other) {
        if (size != other->getSize())
            return false;

        Node<E>* temp1 = current->next;
        Node<E>* temp2 = other->current->next;

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
     * Comienza la búsqueda a partir del índice indicado.
     *
     * @param element Elemento a buscar en la lista.
     * @param start Índice desde el cual iniciar la búsqueda (por defecto 0).
     * @return El índice del elemento si se encuentra, o -1 si no existe.
     * @throws runtime_error Si el índice inicial está fuera de los límites de la lista.
     */
    int indexOf(E element, int start = 0) {
        if (start < 0 || start >= size)
            throw runtime_error("Index out of bounds.");

        Node<E>* temp = current->next;
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
     * @brief Determina si la lista contiene un elemento.
     *
     * @param element Elemento a buscar.
     * @return true si el elemento existe en la lista, false en caso contrario.
     */
    bool contains(E element) {
        return indexOf(element, 0) != -1;
    }

    /**
     * @brief Invierte el orden de los elementos en la lista.
     *
     * Reorganiza los enlaces de los nodos de forma que el orden de los elementos se invierta.
     */
    void reverse() {
        Node<E>* prev = nullptr;
        Node<E>* next = nullptr;
        Node<E>* temp = current->next;
        for (int i = 0; i < size; i++) {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }
        current = prev;
    }

    /**
     * @brief Extiende la lista agregando elementos de otra lista circular.
     *
     * Inserta todos los elementos de la otra lista en la lista actual.
     *
     * @param other Puntero a la otra lista circular de la cual se obtendrán los elementos.
     */
    void extend(CircleList<E>* other) {
        Node<E>* temp = other->current->next;
        for (int i = 0; i < other->size; i++) {
            insert(temp->element);
            temp = temp->next;
        }
    }
};
