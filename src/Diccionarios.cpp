#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include "Estructuras/Concretas/Diccionarios/UnsortedArrayDictionary.h"
#include "Estructuras/Concretas/Diccionarios/HashTable.h"
#include "Estructuras/Concretas/Arboles/BSTree.h"
#include "Estructuras/Concretas/Diccionarios/BSTDictionary.h"
#include "Estructuras/Concretas/Arboles/AVLTree.h"
#include "Estructuras/Concretas/Diccionarios/AVLDictionary.h"
#include "Estructuras/Concretas/Arboles/SplayTree.h"
#include "Estructuras/Abstractas/List.h"

using std::string;
using std::runtime_error;
using std::cout;
using std::endl;

int mainTree() {
	srand(time(0));
	AVLTree<int>* arbolAVL = new AVLTree<int>();
	SplayTree<int>* arbolSplay = new SplayTree<int>();
	for (int i = 0; i < 100; i++) {
		int r = rand() % 1000;
		cout << r << " ";
		if (!arbolAVL->contains(r)) {
			arbolAVL->insert(r);
			arbolSplay->insert(r);
		}
	}
	cout << endl;
	cout << "AVL Size: " << arbolAVL->getSize() << endl;
	cout << "BST Size: " << arbolSplay->getSize() << endl;
	List<int>* ordenada = arbolAVL->getElements();
	cout << "AVL: ";
	ordenada->print();
	delete ordenada;
	ordenada = arbolSplay->getElements();
	cout << "BST: ";
	ordenada->print();
	delete ordenada;
	cout << "AVLTree getHeight: " << arbolAVL->getHeight() << endl; 
	cout << "BSTree getHeight: " << arbolSplay->getHeight() << endl; 
	for (int i = 0; i < 300; i++) {
		if (arbolAVL->contains(i)) {
			cout << "AVL Borrando: " << arbolAVL->remove(i) << endl;
			cout << "BST Borrando: " << arbolSplay->remove(i) << endl;
		}
	}
	cout << "Size: " << arbolAVL->getSize() << endl;
	cout << "AVLTree getHeight: " << arbolAVL->getHeight() << endl; 
	cout << "BSTree getHeight: " << arbolSplay->getHeight() << endl;
	cout << "AVL: ";
	arbolAVL->print();
	cout << "BST: ";
	arbolSplay->print();
	cout << "AVLTree getHeight: " << arbolAVL->getHeight() << endl;
	cout << "BSTree getHeight: " << arbolSplay->getHeight() << endl;
	delete arbolAVL;
	delete arbolSplay; 
	return 0;
}

int mainDic() {
	Dictionary<int, string>* nombres = new AVLDictionary<int, string>();
	nombres->insert(9, "Elix");
	nombres->insert(17, "Monsalve");
	nombres->insert(27, "Juan Pa");
	nombres->insert(22, "Adrian");
	nombres->insert(10, "Dcalvog25");
	nombres->insert(11, "Isa Piedra");
	nombres->insert(21, "David");
	nombres->insert(79, "zostercr");
	nombres->insert(8, "sel_alfaro_");
	nombres->print();
	cout << "getValue(22): " << nombres->getValue(22) << endl;
	cout << "getValue(8): " << nombres->getValue(8) << endl;
	cout << "getValue(17): " << nombres->getValue(17) << endl;
	cout << "getValue(79): " << nombres->getValue(79) << endl;
	cout << "getValue(10): " << nombres->getValue(10) << endl;
	try {
		cout << "getValue(100): " << nombres->getValue(100) << endl;
	}
	catch (runtime_error& e) {
		cout << "getValue(100): " << e.what() << endl;
	}
	cout << "remove(79): " << nombres->remove(79) << endl;
	cout << "remove(21): " << nombres->remove(21) << endl;
	cout << "remove(27): " << nombres->remove(27) << endl;
	cout << "remove(9): " << nombres->remove(9) << endl;
	nombres->print();
	nombres->setValue(8, "Sele");
	nombres->setValue(17, "JC Monsalve");
	nombres->print();
	List<int>* llaves = nombres->getKeys();
	llaves->print();
	delete llaves;
	List<string>* valores = nombres->getValues();
	valores->print();
	delete valores;
	delete nombres;
	return 0;
}

int main() {
	AVLTree<int>* arbolAVL = new AVLTree<int>();

	// Inserciones
	int inserciones[] = {73, 62, 14, 65, 12, 72, 91, 18, 45, 69, 0, 15, 99, 35};
	for (int valor : inserciones) {
		arbolAVL->insert(valor);
	}

	// Eliminaciones
	arbolAVL->remove(15);
	arbolAVL->remove(14);

	// Más inserciones
	int inserciones_adicionales[] = {95, 80, 105, 85};
	for (int valor : inserciones_adicionales) {
		arbolAVL->insert(valor);
	}

	// Más eliminaciones
	arbolAVL->remove(0);
	arbolAVL->remove(12);
	arbolAVL->remove(95);

	// Inserciones finales
	arbolAVL->insert(63);
	arbolAVL->insert(64);

	// Eliminación final
	arbolAVL->remove(45);

	// Información final del árbol
	cout << "Tamaño del árbol AVL: " << arbolAVL->getSize() << endl;
	cout << "Altura del árbol AVL: " << arbolAVL->getHeight() << endl;

	cout << "Elementos del árbol AVL (en orden): ";
	arbolAVL->print();

	cout << "Total de rotaciones: " << arbolAVL->getRotationCount() << endl;
	cout << "Total de hojas: " << arbolAVL->getLeafCount() << endl;
	cout << "Total de nodos internos: " << arbolAVL->getInternalNodeCount() << endl;

	// Cambia a List<int>* en lugar de vector<int>
	List<int>* nodesPerLevel = arbolAVL->getNodesPerLevel();

	// Recorre nodesPerLevel y muestra los niveles
	int level = 0;
	for (nodesPerLevel->goToStart(); !nodesPerLevel->atEnd(); nodesPerLevel->next()) {
		cout << "Nivel " << level++ << ": " << nodesPerLevel->getElement() << " nodos" << endl;
	}

	// Liberar memoria
	delete nodesPerLevel;
	delete arbolAVL;

	return 0;
}


