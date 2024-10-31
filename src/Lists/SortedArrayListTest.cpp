#include <iostream>
#include "Structures/Implementations/Lists/SortedArrayList.h"

using std::cout;
using std::endl;

int main() {
    List<int>* list = new SortedArrayList<int>();

    cout << "Testing SortedArrayList:" << endl;
    for (int i = 10; i > 0; i--) {
        list->insert(i); // Elements should remain sorted
    }
    list->print();

    cout << "Removing element: " << list->remove() << endl;
    list->print();

    delete list;
    return 0;
}
