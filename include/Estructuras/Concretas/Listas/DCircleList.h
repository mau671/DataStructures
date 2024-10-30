#pragma once

#include <stdexcept>
#include <iostream>
#include "Estructuras/Nodos/DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class DCircleList {
private:
    DNode<E>* current; // El nodo actual en la lista circular
    int size; // Número de elementos en la lista

public:
    DCircleList() : current(nullptr), size(0) {}

    ~DCircleList() {
        clear();
    }

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

    void clear() {
        while (size > 0) {
            remove();
        }
    }

    E getFront() const {
        if (size == 0)
            throw runtime_error("List is empty.");
        return current->next->element; // Primer elemento en la lista circular
    }

    E getBack() const {
        if (size == 0)
            throw runtime_error("List is empty.");
        return current->element; // `current` apunta al último elemento
    }

    void next() {
        if (size == 0)
            throw runtime_error("List is empty.");
        current = current->next;
    }

    void previous() {
        if (size == 0)
            throw runtime_error("List is empty.");
        current = current->previous;
    }

    int getSize() const {
        return size;
    }

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

    bool contains(E element) const {
        return indexOf(element, 0) != -1;
    }

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

    void extend(DCircleList<E>* other) {
        DNode<E>* temp = other->current->next;
        for (int i = 0; i < other->size; i++) {
            insert(temp->element);
            temp = temp->next;
        }
    }
};
