#pragma once

#include <stdexcept>
#include <iostream>
#include "Structures/Abstract/List.h"
#include "Structures/Common/Nodes/DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class DLinkedList : public List<E> {
private:
	DNode<E>* head;
	DNode<E>* tail;
	DNode<E>* current;
	int size;

public:
	DLinkedList() {
		current = head = new DNode<E>(nullptr, nullptr);
		head->next = tail = new DNode<E>(nullptr, head);
		size = 0;
	}
	~DLinkedList() {
		clear();
		delete head;
		delete tail;
	}
	void insert(E element) {
		current->next = current->next->previous = 
			new DNode<E>(element, current->next, current);
		size++;
	}
	void append(E element) {
		tail->previous = tail->previous->next = 
			new DNode<E>(element, tail, tail->previous);
		size++;
	}
	void set(E element) {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		current->next->element = element;
	}
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
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		return current->next->element;
	}
	void clear() {
		while (head->next != tail) {
			head->next = head->next->next;
			delete head->next->previous;
		}
		current = tail->previous = head;
		size = 0;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail->previous;
	}
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index out of bounds.");
		if (pos <= size / 2) {
			current = head;
			for (int i = 0; i < pos; i++)
				current = current->next;
		}
		else {
			current = tail->previous;
			for (int i = 0; i < size - pos; i++)
				current = current->previous;
		}
	}
	void next() {
		if (current->next != tail)
			current = current->next;
	}
	void previous() {
		if (current != head)
			current = current->previous;
	}
	bool atStart() {
		return current == head;
	}
	bool atEnd() {
		return current->next == tail; 
	}
	int getPos() {
		int pos = 0;
		DNode<E>* temp = head;
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

	void reverse() {
		DNode<E>* temp = head;
		head = tail;
		tail = temp;
		current = head;
	}

	void extend(List<E>* other) {
		goToEnd();
		for (int i = 0; i < other->getSize(); i++) {
			append(other->getElement());
			other->next();
		}
	}

};

