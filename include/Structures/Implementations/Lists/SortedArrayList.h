#pragma once
#include "Structures/Implementations/Lists/ArrayList.h"

/* Clase que implementa una lista ordenada utilizando herencia
   especializando la clase ArrayList */

template <typename E>
class SortedArrayList : public ArrayList<E> {
public:
	SortedArrayList(int max = DEFAULT_MAX) : ArrayList<E>(max) {}
	void insert(E element) {
		ArrayList<E>::goToStart();
		while (!ArrayList<E>::atEnd() && element >= ArrayList<E>::getElement())
			ArrayList<E>::next();
		ArrayList<E>::insert(element);
	}
	void append(E element) {
		insert(element);
	}
};

