#pragma once

#include <stdexcept>
#include <iostream>
#include "Structures/Abstract/List.h"
#include "Structures/Common/Nodes/Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class LinkedList : public List<E> {
private:
    Node<E>* head;
    Node<E>* tail;
    Node<E>* current;
    int size;

    // Lista de nodos libres
    Node<E>* freeNodes;

    // Métodos privados para manejar la lista de nodos libres
    Node<E>* getFreeNode(E element, Node<E>* next = nullptr) {
        if (freeNodes != nullptr) {
            Node<E>* temp = freeNodes;
            freeNodes = freeNodes->next;
            temp->element = element;
            temp->next = next;
            return temp;
        }
        return new Node<E>(element, next);
    }

    void releaseNode(Node<E>* node) {
        node->next = freeNodes;
        freeNodes = node;
    }

public:
    LinkedList() {
        current = head = tail = new Node<E>();
        freeNodes = nullptr;
        size = 0;
    }

    ~LinkedList() {
        clear();
        delete head;
        while (freeNodes != nullptr) {
            Node<E>* temp = freeNodes;
            freeNodes = freeNodes->next;
            delete temp;
        }
    }

    void insert(E element) {
        current->next = getFreeNode(element, current->next);
        if (current == tail)
            tail = tail->next;
        size++;
    }

    void append(E element) {
        tail = tail->next = getFreeNode(element);
        size++;
    }

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

    E getElement() {
        if (size == 0)
            throw runtime_error("List is empty");
        if (current == tail)
            throw runtime_error("No current element.");
        return current->next->element;
    }

    void clear() {
        while (head->next != nullptr) {
            current = head->next;
            head->next = current->next;
            releaseNode(current);
        }
        current = tail = head;
        size = 0;
    }

    void goToStart() {
        current = head;
    }

    void goToEnd() {
        current = tail;
    }

    void goToPos(int pos) {
        if (pos < 0 || pos > size)
            throw runtime_error("Index out of bounds.");
        current = head;
        for (int i = 0; i < pos; i++)
            current = current->next;
    }

    void next() {
        if (current != tail)
            current = current->next;
    }

    void previous() {
        if (current != head) {
            Node<E>* temp = head;
            while (temp->next != current)
                temp = temp->next;
            current = temp;
        }
    }

    bool atStart() {
        return current == head;
    }

    bool atEnd() {
        return current == tail;
    }

    int getPos() {
        int pos = 0;
        Node<E>* temp = head;
        while (temp != current) {
            temp = temp->next;
            pos++;
        }
        return pos;
    }

    int getSize() {
        return size;
    }

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

    bool contains(E element) {
        return indexOf(element, 0) != -1;
    }

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

    void extend(List<E>* other) {
        Node<E>* temp = dynamic_cast<LinkedList<E>*>(other)->head->next;
        while (temp != nullptr) {
            append(temp->element);
            temp = temp->next;
        }
    }
};
