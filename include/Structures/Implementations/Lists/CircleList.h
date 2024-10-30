#pragma once

#include <stdexcept>
#include <iostream>
#include "Structures/Common/Nodes/Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class CircleList {
private:
    Node<E>* current;
    int size;

public:
    CircleList() : current(nullptr), size(0) {}

    ~CircleList() {
        clear();
    }

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

    E remove() {
        if (size == 0)
            throw runtime_error("List is empty.");

        E result = current->next->element;
        Node<E>* temp = current->next;

        if (size == 1) { // If there's only one element
            current = nullptr;
        } else {
            current->next = temp->next;
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

    E getFront() {
        if (size == 0)
            throw runtime_error("List is empty.");
        return current->next->element; // First element in the circular list
    }

    E getBack() {
        if (size == 0)
            throw runtime_error("List is empty.");
        return current->element; // Current points to the last element
    }

    void next() {
        if (size == 0)
            throw runtime_error("List is empty.");
        current = current->next;
    }

    void previous() {
        if (size == 0)
            throw runtime_error("List is empty.");

        Node<E>* temp = current;
        while (temp->next != current) { // Find the previous node
            temp = temp->next;
        }
        current = temp;
    }

    int getSize() {
        return size;
    }

    void print() {
        if (size == 0) {
            cout << "List is empty." << endl;
            return;
        }

        Node<E>* temp = current->next; // Start from the front
        cout << "[ ";
        for (int i = 0; i < size; i++) {
            cout << temp->element << " ";
            temp = temp->next;
        }
        cout << "]" << endl;
    }

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

    bool contains(E element) {
        return indexOf(element, 0) != -1;
    }

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

    void extend(CircleList<E>* other) {
        Node<E>* temp = other->current->next;
        for (int i = 0; i < other->size; i++) {
            insert(temp->element);
            temp = temp->next;
        }
    }

};
