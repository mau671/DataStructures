/**
 * @file LinkedList.h
 * @brief Implementación de una lista enlazada simple con manejo de nodos libres.
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
#include "Structures/Common/Nodes/Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Clase que implementa una lista enlazada simple.
 * 
 * @tparam E Tipo de elementos almacenados en la lista.
 */
template <typename E>
class LinkedList : public List<E> {
private:
    Node<E>* head;    ///< Puntero al primer nodo de la lista.
    Node<E>* tail;    ///< Puntero al último nodo de la lista.
    Node<E>* current; ///< Puntero al nodo actual.
    int size;         ///< Número de elementos en la lista.

    Node<E>* freeNode; ///< Lista de nodos libres para reutilización.

    /**
     * @brief Obtiene un nodo libre de la lista de nodos libres o crea uno nuevo si no hay disponibles.
     * 
     * @param element Elemento que almacenará el nodo.
     * @param next Puntero al siguiente nodo (opcional).
     * @return Puntero al nodo recién asignado.
     */
    Node<E>* getFreeNode(E element, Node<E>* next = nullptr) {
        if (freeNode != nullptr) {
            Node<E>* temp = freeNode;
            freeNode = freeNode->next;
            temp->element = element;
            temp->next = next;
            return temp;
        }
        return new Node<E>(element, next);
    }

    /**
     * @brief Libera un nodo y lo agrega a la lista de nodos libres.
     * 
     * @param node Puntero al nodo que se va a liberar.
     */
    void releaseNode(Node<E>* node) {
        node->next = freeNode;
        freeNode = node;
    }

public:
    /**
     * @brief Constructor que inicializa una lista enlazada vacía.
     */
    LinkedList() {
        current = head = tail = new Node<E>();
        freeNode = nullptr;
        size = 0;
    }

    /**
     * @brief Destructor que libera toda la memoria asociada con la lista.
     */
    ~LinkedList() {
        clear();
        delete head;
        while (freeNode != nullptr) {
            Node<E>* temp = freeNode;
            freeNode = freeNode->next;
            delete temp;
        }
    }

    /**
     * @brief Inserta un elemento en la posición actual.
     * 
     * @param element Elemento a insertar.
     */
    void insert(E element) {
        current->next = getFreeNode(element, current->next);
        if (current == tail)
            tail = tail->next;
        size++;
    }

    /**
     * @brief Agrega un elemento al final de la lista.
     * 
     * @param element Elemento a agregar.
     */
    void append(E element) {
        tail = tail->next = getFreeNode(element);
        size++;
    }

    /**
     * @brief Elimina y devuelve el elemento en la posición actual.
     * 
     * @return Elemento eliminado.
     * @throw runtime_error Si la lista está vacía o no hay un elemento actual.
     */
    E remove() {
        if (size == 0)
            throw runtime_error("List is empty");
        if (current == tail)
            throw runtime_error("No current element.");
        E result = current->next->element;
        Node<E>* temp = current->next;
        if (current->next == tail)
            tail = current;
        current->next = temp->next;
        releaseNode(temp);
        size--;
        return result;
    }

    /**
     * @brief Devuelve el elemento en la posición actual.
     * 
     * @return Elemento en la posición actual.
     * @throw runtime_error Si la lista está vacía o no hay un elemento actual.
     */
    E getElement() {
        if (size == 0)
            throw runtime_error("List is empty");
        if (current == tail)
            throw runtime_error("No current element.");
        return current->next->element;
    }

    /**
     * @brief Limpia todos los elementos de la lista.
     */
    void clear() {
        while (head->next != nullptr) {
            current = head->next;
            head->next = current->next;
            releaseNode(current);
        }
        current = tail = head;
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
        current = tail;
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
        current = head;
        for (int i = 0; i < pos; i++)
            current = current->next;
    }

    /**
     * @brief Mueve el puntero actual al siguiente elemento.
     */
    void next() {
        if (current != tail)
            current = current->next;
    }

    /**
     * @brief Mueve el puntero actual al elemento anterior.
     */
    void previous() {
        if (current != head) {
            Node<E>* temp = head;
            while (temp->next != current)
                temp = temp->next;
            current = temp;
        }
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
        return current == tail;
    }

    /**
     * @brief Devuelve la posición actual del puntero en la lista.
     * 
     * @return Posición actual del puntero.
     */
    int getPos() {
        int pos = 0;
        Node<E>* temp = head;
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
        Node<E>* temp = head->next;
        while (temp != nullptr) {
            if (temp == current->next)
                cout << "*";
            cout << temp->element << " ";
            temp = temp->next;
        }
        if (current == tail)
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
        Node<E>* temp = head;
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
        return indexOf(element, 0) != -1;
    }

    /**
     * @brief Invierte el orden de los elementos en la lista.
     */
    void reverse() {
        Node<E>* prev = nullptr;
        Node<E>* next = nullptr;
        Node<E>* temp = head->next;
        while (temp != nullptr) {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }
        tail = head->next;
        head->next = prev;
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
        Node<E>* temp1 = head->next;
        Node<E>* temp2 = dynamic_cast<LinkedList<E>*>(other)->head->next;
        while (temp1 != nullptr) {
            if (temp1->element != temp2->element)
                return false;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        return true;
    }

    /**
     * @brief Extiende la lista actual con los elementos de otra lista.
     * 
     * @param other Lista cuyos elementos se agregarán.
     */
    void extend(List<E>* other) {
        Node<E>* temp = dynamic_cast<LinkedList<E>*>(other)->head->next;
        while (temp != nullptr) {
            append(temp->element);
            temp = temp->next;
        }
    }

    /**
     * @brief Establece un nuevo valor para el elemento en la posición actual.
     * 
     * @param element Nuevo valor a establecer.
     * @throw runtime_error Si la lista está vacía o no hay un elemento actual.
     */
    void set(E element) {
        if (size == 0)
            throw runtime_error("List is empty");
        if (current == tail)
            throw runtime_error("No current element.");
        current->next->element = element;
    }
};
