#include <iostream>

#include "Structures/Implementations/Lists/DCircleList.h"

using std::cout;
using std::endl;

int main() {
    DCircleList<int>* list = new DCircleList<int>();

    cout << "Testing DCircleList:" << endl;
    for (int i = 0; i < 10; i++) {
        list->insert(i);
    }
    list->print();

    cout << "Removing element: " << list->remove() << endl;
    list->print();

    cout << "Inserting element at position 0" << endl;
    list->insert(100);
    list->print();

    delete list;
    return 0;
}
