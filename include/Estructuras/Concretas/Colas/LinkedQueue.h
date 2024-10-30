#pragma once
#include <iostream>
#include <stdexcept>
#include "Estructuras/Abstractas/Queue.h"
#include "Estructuras/Nodos/Node.h"

using std::cout;
using std::endl;
using std::runtime_error;

template <typename E>
class LinkedQueue : public Queue<E> {
private:
    Node<E>* front;
    Node<E>* back;
    int size;

public:
    LinkedQueue() {
        front = back = new Node<E>();
        size = 0;
    }

    ~LinkedQueue() {
        clear();
        delete front;
    }

    void enqueue(E element) {
        back = back->next = new Node<E>(element);
        size++;
    }

    E dequeue() {
        if (size == 0) throw runtime_error("Queue is empty");
        Node<E>* temp = front->next;
        E result = temp->element;
        front->next = temp->next;
        delete temp;
        size--;
        if (size == 0) back = front;
        return result;
    }

    E frontValue() {
        if (size == 0) throw runtime_error("Queue is empty");
        return front->next->element;
    }

    void clear() {
        while (front->next != nullptr) {
            Node<E>* temp = front->next;
            front->next = temp->next;
            delete temp;
        }
        back = front;
        size = 0;
    }

    bool isEmpty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }

    void enqueueFront(E element) {
        Node<E>* newNode = new Node<E>(element);
        newNode->next = front->next;
        front->next = newNode;
        if (size == 0) {
            back = newNode;
        }
        size++;
    }

    E dequeueBack() {
        if (size == 0) throw runtime_error("Queue is empty");
        Node<E>* temp = front;
        while (temp->next != back) {
            temp = temp->next;
        }
        E result = back->element;
        delete back;
        back = temp;
        back->next = nullptr;
        size--;
        return result;
    }

    E backValue() {
        if (size == 0) throw runtime_error("Queue is empty");
        return back->element;
    }

    void print() {
        cout << "[ ";
        Node<E>* temp = front->next;
        while (temp != nullptr) {
            cout << temp->element << " ";
            temp = temp->next;
        }
        cout << "]" << endl;
    }
};
