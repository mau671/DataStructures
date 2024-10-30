#pragma once
#include <iostream>
#include <stdexcept>
#include "Estructuras/Abstractas/Queue.h"
#include "Estructuras/Abstractas/PriorityQueue.h"

using std::cout;
using std::endl;
using std::runtime_error;

template <typename E>
class LinkedPriorityQueue : public PriorityQueue<E> {
private:
    LinkedQueue<E> *queues;
    int size;
    int priorities;

public:
    LinkedPriorityQueue(int priorities) {
        if (priorities <= 0) throw runtime_error("Invalid number of priorities");
        queues = new LinkedQueue<E>[priorities];
        size = 0;
        this->priorities = priorities;
    }

    ~LinkedPriorityQueue() {
        delete[] queues;
    }

    void insert(E element, int priority = 0) {
        if (priority < 0 || priority >= priorities) throw runtime_error("Invalid priority");
        queues[priority].enqueue(element);
        size++;
    }

    E min() {
        if (size == 0) throw runtime_error("Queue is empty");
        for (int i = 0; i < priorities; i++) {
            if (!queues[i].isEmpty()) return queues[i].frontValue();
        }
        throw runtime_error("Queue not found");
    }

    E removeMin() {
        if (size == 0) throw runtime_error("Queue is empty");
        for (int i = 0; i < priorities; i++) {
            if (!queues[i].isEmpty()) {
                size--;
                return queues[i].dequeue();
            }
        }
        throw runtime_error("Queue not found");
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }


};