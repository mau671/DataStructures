#include <iostream>
#include "Structures/Implementations/Lists/DLinkedList.h"

using std::cout;
using std::endl;

int main() {
    List<int>* list = new DLinkedList<int>();

    cout << "Testing DLinkedList:" << endl;
    for (int i = 0; i < 10; i++) {
        list->append(i);
    }
    list->print();

    cout << "Removing element: " << list->remove() << endl;
    list->print();

    cout << "Inserting element at position 0" << endl;
    list->goToStart();
    list->insert(100);
    list->print();

    delete list;
    return 0;
}
