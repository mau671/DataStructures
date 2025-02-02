#include <iostream>
#include "Structures/Implementations/Lists/OrderedArrayList.h"

using std::cout;
using std::endl;

int main() {
    List<int>* list = new OrderedArrayList<int>();

    cout << "Testing OrderedArrayList:" << endl;
    for (int i = 10; i > 0; i--) {
        list->insert(i); // Elements should remain ordered
    }
    list->print();

    cout << "Removing element: " << list->remove() << endl;
    list->print();

    delete list;
    return 0;
}
