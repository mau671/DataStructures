#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include <queue>
#include "Structures/Common/Nodes/BSTNode.h"
#include "Structures/Implementations/Lists/DLinkedList.h"
#include "Structures/Implementations/Queues/LinkedQueue.h"


using std::runtime_error;
using std::cout;
using std::endl;
using std::vector;
using std::queue;

template <typename E>
class AVLTree {
private:
	AVLTree(const AVLTree<E>& other) {}
	void operator =(const AVLTree<E>& other) {}

	BSTNode<E>* root;
	int rotationCount;

	BSTNode<E>* insertAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			return new BSTNode<E>(element);
		// el siguiente if puede eliminarse si la estructura
		// permite elementos repetidos.
		if (element == current->element)
			throw runtime_error("Duplicated element.");
		if (element < current->element) {
			current->left = insertAux(current->left, element);
			return rebalanceLeft(current);
		}
		else {
			current->right = insertAux(current->right, element);
			return rebalanceRight(current);
		}

	}
	bool containsAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			return false;
		if (element == current->element)
			return true;
		if (element < current->element)
			return containsAux(current->left, element);
		else
			return containsAux(current->right, element);
	}
	E findAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			throw runtime_error("Element not found.");
		if (element == current->element)
			return current->element;
		if (element < current->element)
			return findAux(current->left, element);
		else
			return findAux(current->right, element);
	}
	BSTNode<E>* removeAux(BSTNode<E>* current, E element, E* result) {
		if (current == nullptr)
			throw runtime_error("Element not found.");
		if (element < current->element) {
			current->left = removeAux(current->left, element, result);
			return rebalanceRight(current);
		}
		if (element > current->element) {
			current->right = removeAux(current->right, element, result);
			return rebalanceLeft(current);
		}
		else { // es igual
			*result = current->element;
			int childrenCount = current->childrenCount();
			if (childrenCount == 0) {
				delete current;
				return nullptr;
			}
			if (childrenCount == 1) {
				BSTNode<E>* child = current->onlyChild();
				delete current;
				return child;
			}
			else { // tiene dos hijos
				BSTNode<E>* successor = findMin(current->right);
				swap(current, successor);
				current->right = removeAux(current->right, element, result);
				return current;
			}
		}
	}
	BSTNode<E>* findMin(BSTNode<E>* current) {
		while (current->left != nullptr)
			current = current->left;
		return current;
	}
	void swap(BSTNode<E>* n1, BSTNode<E>* n2) {
		E temp = n1->element;
		n1->element = n2->element;
		n2->element = temp;
	}
	void clearAux(BSTNode<E>* current) {
		if (current == nullptr)
			return;
		clearAux(current->left);
		clearAux(current->right);
		delete current;
	}
	void getElementsAux(BSTNode<E>* current, List<E>* elements) {
		if (current == nullptr)
			return;
		getElementsAux(current->left, elements);
		elements->append(current->element);
		getElementsAux(current->right, elements);
	}
	int getSizeAux(BSTNode<E>* current) {
		if (current == nullptr)
			return 0;
		return 1 + getSizeAux(current->left) + getSizeAux(current->right);
	}
	// Incrementa el contador de rotaciones en los métodos de rotación
	BSTNode<E>* rotateRight(BSTNode<E>* current) {
		if (current->left == nullptr)
			throw runtime_error("Can't rotate right with null left child.");
		BSTNode<E>* temp = current->left;
		current->left = temp->right;
		temp->right = current;
		rotationCount++; // Contar rotación
		return temp;
	}

	BSTNode<E>* rotateLeft(BSTNode<E>* current) {
		if (current->right == nullptr)
			throw runtime_error("Can't rotate left with null right child.");
		BSTNode<E>* temp = current->right;
		current->right = temp->left;
		temp->left = current;
		rotationCount++; // Contar rotación
		return temp;
	}

	int height(BSTNode<E>* current) {
		if (current == nullptr)
			return 0;
		int lh = height(current->left);
		int rh = height(current->right);
		return 1 + (lh > rh? lh : rh);
	}
	BSTNode<E>* rebalanceLeft(BSTNode<E>* current) {
		int lh = height(current->left);
		int rh = height(current->right);
		if (lh - rh > 1) {
			int llh = height(current->left->left);
			int lrh = height(current->left->right);
			if (llh >= lrh) {
				return rotateRight(current);
			}
			else {
				current->left = rotateLeft(current->left);
				return rotateRight(current);
			}
		}
		return current;
	}
	BSTNode<E>* rebalanceRight(BSTNode<E>* current) {
		int rh = height(current->right);
		int lh = height(current->left);
		if (rh - lh > 1) {
			int rrh = height(current->right->right);
			int rlh = height(current->right->left);
			if (rrh >= rlh) {
				return rotateLeft(current);
			}
			else {
				current->right = rotateRight(current->right);
				return rotateLeft(current);
			}
		}
		return current;
	}

	// Función auxiliar para contar hojas y nodos internos
	void countNodes(BSTNode<E>* current, int& leaves, int& internals) const {
		if (current == nullptr) return;
		if (current->left == nullptr && current->right == nullptr) {
			leaves++;
		} else {
			internals++;
			countNodes(current->left, leaves, internals);
			countNodes(current->right, leaves, internals);
		}
	}

public:
	AVLTree() {
		root = nullptr;
	}
	~AVLTree() {
		clear();
	}
	void insert(E element) {
		root = insertAux(root, element);
	}
	bool contains(E element) {
		return containsAux(root, element);
	}
	E find(E element) {
		return findAux(root, element);
	}
	E remove(E element) {
		E result;
		root = removeAux(root, element, &result);
		return result;
	}
	void clear() {
		clearAux(root);
		root = nullptr;
	}
	List<E>* getElements() {
		List<E>* elements = new DLinkedList<E>();
		getElementsAux(root, elements);
		return elements;
	}
	int getSize() {
		return getSizeAux(root);
	}
	void print() {
		List<E>* elements = getElements();
		elements->print();
		delete elements;
	}
	int getHeight() {
		return height(root);
	}

	// Método para obtener el número de hojas
	int getLeafCount() const {
		int leaves = 0, internals = 0;
		countNodes(root, leaves, internals);
		return leaves;
	}

	// Método para obtener el número de nodos internos
	int getInternalNodeCount() const {
		int leaves = 0, internals = 0;
		countNodes(root, leaves, internals);
		return internals;
	}

	// Método para obtener el número de nodos por nivel
	List<int>* getNodesPerLevel() const {
		List<int>* levels = new DLinkedList<int>(); // Cambia esta línea si deseas usar otra implementación de lista
		if (root == nullptr) return levels;

		LinkedQueue<BSTNode<E>*> q;
		q.enqueue(root);

		while (!q.isEmpty()) {
			int levelSize = q.getSize();
			levels->append(levelSize); // Añadir el tamaño del nivel actual a la lista de niveles

			for (int i = 0; i < levelSize; ++i) {
				BSTNode<E>* node = q.dequeue(); // Desencolamos el nodo
				if (node->left) q.enqueue(node->left);   // Encolamos el hijo izquierdo si existe
				if (node->right) q.enqueue(node->right); // Encolamos el hijo derecho si existe
			}
		}

		return levels;
	}

	// Método para obtener el número de rotaciones
	int getRotationCount() const {
		return rotationCount;
	}
};



