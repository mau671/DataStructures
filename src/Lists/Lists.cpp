#include <iostream>
#include "Structures/Abstract/List.h"
#include "Structures/Implementations/Lists/ArrayList.h"
#include "Structures/Implementations/Lists/CircleList.h"
#include "Structures/Implementations/Lists/DCircleList.h"
#include "Structures/Implementations/Lists/DLinkedList.h"
#include "Structures/Implementations/Lists/LinkedList.h"
#include "Structures/Implementations/Lists/OrderedArrayList.h"
#include "Structures/Implementations/Lists/SortedArrayList.h"

using std::cout;
using std::endl;

/**
 * @brief Muestra las opciones de tipos de listas disponibles.
 */
void showListOptions() {
    cout << "Seleccione el tipo de lista a utilizar:" << endl;
    cout << "1. ArrayList" << endl;
    cout << "2. CircleList" << endl;
    cout << "3. DCircleList" << endl;
    cout << "4. DLinkedList" << endl;
    cout << "5. LinkedList" << endl;
    cout << "6. OrderedArrayList" << endl;
    cout << "7. SortedArrayList" << endl;
}

/**
 * @brief Crea una lista dinámicamente según la opción seleccionada.
 *
 * @param option Opción seleccionada por el usuario.
 * @return Puntero a la lista creada.
 */
template <typename E>
List<E>* createList(int option) {
    switch (option) {
        case 1:
            return new ArrayList<E>();
        case 2:
            //return new CircleList<E>();
            cout << "Opción no implementada." << endl;
        case 3:
            //return new DCircleList<E>();
            cout << "Opción no implementada." << endl;
        case 4:
            return new DLinkedList<E>();
        case 5:
            return new LinkedList<E>();
        case 6:
            return new OrderedArrayList<E>();
        case 7:
            return new SortedArrayList<E>();
        default:
            throw std::runtime_error("Opción no válida.");
    }
}

/**
 * @brief Realiza pruebas automáticas en la lista.
 *
 * @tparam E Tipo de los elementos almacenados en la lista.
 * @param list Puntero a la lista en la que se realizarán las pruebas.
 */
template <typename E>
void runAutomaticTests(List<E>* list) {
    cout << "Ejecutando pruebas automáticas..." << endl;

    // Agregar elementos
    for (int i = 0; i < 10; i++) {
        list->append(i);
    }
    cout << "Lista después de agregar elementos:" << endl;
    list->print();

    // Eliminar un elemento
    cout << "Eliminando elemento: " << list->remove() << endl;
    cout << "Lista después de eliminar un elemento:" << endl;
    list->print();

    // Insertar un elemento en la posición inicial
    list->goToStart();
    list->insert(100);
    cout << "Lista después de insertar 100 al inicio:" << endl;
    list->print();

    // Invertir la lista
    cout << "Invertiendo la lista..." << endl;
    list->reverse();
    list->print();
}

/**
 * @brief Muestra un menú interactivo para realizar operaciones manuales en la lista.
 *
 * @tparam E Tipo de los elementos almacenados en la lista.
 * @param list Puntero a la lista en la que se realizarán las operaciones.
 */
template <typename E>
void manualMenu(List<E>* list) {
    int option;
    E element;
    int position;

    while (true) {
        cout << "\nMenú Manual:" << endl;
        cout << "1. Insertar elemento" << endl;
        cout << "2. Agregar elemento al final" << endl;
        cout << "3. Eliminar elemento" << endl;
        cout << "4. Obtener elemento actual" << endl;
        cout << "5. Limpiar lista" << endl;
        cout << "6. Ir al inicio" << endl;
        cout << "7. Ir al final" << endl;
        cout << "8. Ir a una posición específica" << endl;
        cout << "9. Avanzar cursor" << endl;
        cout << "10. Retroceder cursor" << endl;
        cout << "11. Imprimir lista" << endl;
        cout << "12. Salir" << endl;

        cout << "Seleccione una opción: ";
        std::cin >> option;

        switch (option) {
            case 1:
                cout << "Ingrese el elemento a insertar: ";
                std::cin >> element;
                list->insert(element);
                break;
            case 2:
                cout << "Ingrese el elemento a agregar al final: ";
                std::cin >> element;
                list->append(element);
                break;
            case 3:
                try {
                    cout << "Elemento eliminado: " << list->remove() << endl;
                } catch (const std::runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;
            case 4:
                try {
                    cout << "Elemento actual: " << list->getElement() << endl;
                } catch (const std::runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;
            case 5:
                list->clear();
                cout << "Lista limpiada." << endl;
                break;
            case 6:
                list->goToStart();
                cout << "Cursor movido al inicio." << endl;
                break;
            case 7:
                list->goToEnd();
                cout << "Cursor movido al final." << endl;
                break;
            case 8:
                cout << "Ingrese la posición: ";
                std::cin >> position;
                list->goToPos(position);
                cout << "Cursor movido a la posición " << position << "." << endl;
                break;
            case 9:
                list->next();
                cout << "Cursor avanzado." << endl;
                break;
            case 10:
                list->previous();
                cout << "Cursor retrocedido." << endl;
                break;
            case 11:
                list->print();
                break;
            case 12:
                cout << "Saliendo del menú manual..." << endl;
                return;
            default:
                cout << "Opción no válida." << endl;
        }
    }
}

/**
 * @brief Función principal del programa.
 */
int main() {
    int listOption, testOption;

    // Mostrar opciones de listas
    showListOptions();
    cout << "Seleccione una opción: ";
    std::cin >> listOption;

    // Crear la lista dinámicamente
    List<int>* list = nullptr;
    try {
        list = createList<int>(listOption);
    } catch (const std::runtime_error& e) {
        cout << e.what() << endl;
        return 1;
    }

    // Preguntar si desea realizar pruebas automáticas o manuales
    cout << "Seleccione el tipo de prueba:" << endl;
    cout << "1. Pruebas automáticas" << endl;
    cout << "2. Pruebas manuales" << endl;
    cout << "Opción: ";
    std::cin >> testOption;

    if (testOption == 1) {
        // Ejecutar pruebas automáticas
        runAutomaticTests(list);
    } else if (testOption == 2) {
        // Ejecutar menú manual
        manualMenu(list);
    } else {
        cout << "Opción no válida." << endl;
    }

    // Liberar memoria
    delete list;
    return 0;
}