#pragma once

#include <stdexcept>
#include <iostream>
#include "Structures/Abstract/Stack.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayStack : public Stack<E> {
private:
	E* elements;
	int max;
	int top;

public:
	ArrayStack(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("Invalid max size.");
		elements = new E[max];
		this->max = max;
		top = 0;
	}
	~ArrayStack() {
		delete[] elements;
	}
	void push(E element) {
		if (top == max)
			throw runtime_error("Stack overflow.");
		elements[top] = element;
		top++;
	}
	E pop() {
		if (top == 0)
			throw runtime_error("Stack is empty.");
		top--;
		return elements[top];
	}
	E topValue() {
		if (top == 0)
			throw runtime_error("Stack is empty.");
		return elements[top - 1];
	}
	void clear() {
		top = 0;
		//delete[] elements;
		//elements = new E[max];
	}
	bool isEmpty() {
		return top == 0;
	}
	int getSize() {
		return top;
	}
	void print() {
		cout << "[ ";
		for (int i = top - 1; i >= 0; i--)
			cout << elements[i] << " ";
		cout << "]" << endl;
	}
};

