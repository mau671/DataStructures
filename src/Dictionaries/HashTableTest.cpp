#include <iostream>
#include <string>
#include <stdexcept>
#include "Structures/Implementations/Dictionaries/HashTable.h"
#include "Structures/Abstract/List.h"

using std::string;
using std::runtime_error;
using std::cout;
using std::endl;

int main() {
	Dictionary<int, string>* nombres = new HashTable<int, string>();
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