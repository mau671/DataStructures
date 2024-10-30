#pragma once

template <typename E>
class Queue {
private:
	Queue(const Queue<E>& other) {} // Protect copy constructor
	void operator=(const Queue<E>& other) {} // Protect assignment operator

public:
	Queue() {} // Default constructor
	virtual ~Queue() {} // Base destructor

	// Métodos originales de la clase Queue
	virtual void enqueue(E element) = 0; // Insertar un elemento al final de la cola
	virtual E dequeue() = 0; // Eliminar y retornar el elemento al frente de la cola
	virtual E frontValue() = 0; // Retornar el elemento en el frente de la cola
	virtual void clear() = 0; // Remover todos los elementos de la cola
	virtual bool isEmpty() = 0; // Retornar true si la cola está vacía
	virtual int getSize() = 0; // Retornar el número de elementos en la cola
	virtual void print() = 0; // Imprimir la cola

	// Nuevos métodos para soporte de Deque
	virtual void enqueueFront(E element) = 0; // Insertar un elemento al frente de la cola
	virtual E dequeueBack() = 0; // Eliminar y retornar el elemento al final de la cola
	virtual E backValue() = 0; // Retornar el elemento en el final de la cola
};
