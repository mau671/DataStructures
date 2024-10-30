#pragma once

#include <iostream>
#include <stdexcept>
#include "Estructuras/Abstractas/Dictionary.h"
#include "Estructuras/Concretas/KVPair.h"
#include "Estructuras/Concretas/Arboles/AVLTree.h"
#include "Estructuras/Concretas/Listas/DLinkedList.h"

template <typename K, typename V>
class AVLDictionary : public Dictionary<K, V> {
private:
	AVLTree<KVPair<K, V>>* pairs;

public:
	AVLDictionary(const AVLDictionary<K, V>& other) = delete;
	void operator =(const AVLDictionary<K, V>& other) = delete;

	AVLDictionary() {
		pairs = new AVLTree<KVPair<K, V>>();
	}

	~AVLDictionary() {
		delete pairs;
	}

	void insert(K key, V value) {
		KVPair<K, V> pair(key, value);
		pairs->insert(pair);
	}

	V remove(K key) {
		KVPair<K, V> pair(key);
		pair = pairs->remove(pair);
		return pair.value;
	}

	V getValue(K key) {
		KVPair<K, V> pair(key);
		pair = pairs->find(pair);
		return pair.value;
	}

	void setValue(K key, V value) {
		KVPair<K, V> pair(key, value);
		pairs->remove(pair);
		pairs->insert(pair);
	}

	bool contains(K key) {
		KVPair<K, V> pair(key);
		return pairs->contains(pair);
	}

	List<K>* getKeys() {
		List<KVPair<K, V>>* items = pairs->getElements();
		List<K>* keys = new DLinkedList<K>();
		while (!items->atEnd()) {
			auto pair = items->getElement();
			keys->append(pair.key);
			items->next();
		}
		delete items;
		return keys;
	}

	List<V>* getValues() {
		List<KVPair<K, V>>* items = pairs->getElements();
		List<V>* values = new DLinkedList<V>();
		while (!items->atEnd()) {
			auto pair = items->getElement();
			values->append(pair.value);
			items->next();
		}
		delete items;
		return values;
	}

	int getSize() {
		return pairs->getSize();
	}

	void print() {
		pairs->print();
	}

};

