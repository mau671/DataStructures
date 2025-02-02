/**
 * @file ArrayList.h
 * @brief Implementación de una lista utilizando un arreglo dinámico.
 *
 * Proporciona operaciones de inserción, eliminación, búsqueda y manipulación de elementos.
 *
 * @author Profesor Mauricio Aviles Cisneros
 * @author Mauricio González Prendas
 */

#pragma once

#define DEFAULT_MAX 1024

#include <stdexcept>
#include <iostream>
#include "Structures/Abstract/List.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Clase plantilla que implementa una lista utilizando un arreglo dinámico.
 *
 * Esta clase permite almacenar elementos en un arreglo que se expande dinámicamente,
 * ofreciendo operaciones para insertar, eliminar, buscar, invertir, comparar, entre otras.
 *
 * @tparam E Tipo de dato que se almacena en la lista.
 */
template <typename E>
class ArrayList : public List<E> {
protected:
    E* elements; ///< Arreglo dinámico que almacena los elementos de la lista.
    int max;     ///< Capacidad máxima actual del arreglo.
    int size;    ///< Número de elementos actualmente almacenados en la lista.
    int pos;     ///< Posición actual en la lista.

private:
    /**
     * @brief Expande la capacidad del arreglo cuando éste se encuentra lleno.
     *
     * Crea un nuevo arreglo con el doble de la capacidad actual, copia los elementos
     * existentes y libera la memoria del arreglo antiguo.
     */
    void expand() {
        E* newElements = new E[max * 2];
        for (int i = 0; i < size; i++)
            newElements[i] = elements[i];
        delete[] elements;
        elements = newElements;
        max *= 2;
    }

public:
    /**
     * @brief Constructor que inicializa la lista con una capacidad máxima.
     *
     * @param max Capacidad máxima inicial de la lista. Si no se especifica, se utiliza DEFAULT_MAX.
     * @throws runtime_error Si el tamaño máximo es menor que 1.
     */
    ArrayList(int max = DEFAULT_MAX) {
        if (max < 1)
            throw runtime_error("Invalid max size.");
        elements = new E[max];
        this->max = max;
        size = 0;
        pos = 0;
    }

    /**
     * @brief Destructor que libera la memoria utilizada por el arreglo dinámico.
     */
    ~ArrayList() {
        delete[] elements;
    }

    /**
     * @brief Inserta un elemento en la posición actual de la lista.
     *
     * Si el arreglo está lleno, se expande su capacidad antes de insertar.
     * Los elementos a partir de la posición actual se desplazan hacia la derecha.
     *
     * @param element Elemento a insertar.
     */
    void insert(E element) {
        if (size == max)
            expand();
        for (int i = size; i > pos; i--)
            elements[i] = elements[i - 1];
        elements[pos] = element;
        size++;
    }

    /**
     * @brief Agrega un elemento al final de la lista.
     *
     * Si el arreglo está lleno, se expande su capacidad antes de agregar el elemento.
     *
     * @param element Elemento a agregar.
     */
    void append(E element) {
        if (size == max)
            expand();
        elements[size] = element;
        size++;
    }

    /**
     * @brief Modifica el elemento en la posición actual.
     *
     * @param element Nuevo valor a asignar al elemento en la posición actual.
     * @throws runtime_error Si la lista está vacía o no hay elemento actual.
     */
    void set(E element) {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (pos == size)
            throw runtime_error("No current element.");
        elements[pos] = element;
    }

    /**
     * @brief Elimina y retorna el elemento en la posición actual.
     *
     * Tras la eliminación, los elementos posteriores se desplazan una posición hacia la izquierda.
     *
     * @return El elemento eliminado.
     * @throws runtime_error Si la lista está vacía o no hay elemento actual.
     */
    E remove() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (pos == size)
            throw runtime_error("No current element.");
        E result = elements[pos];
        for (int i = pos + 1; i < size; i++)
            elements[i - 1] = elements[i];
        size--;
        return result;
    }

    /**
     * @brief Obtiene el elemento en la posición actual.
     *
     * @return El elemento en la posición actual.
     * @throws runtime_error Si la lista está vacía o no hay elemento actual.
     */
    E getElement() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (pos == size)
            throw runtime_error("No current element.");
        return elements[pos];
    }

    /**
     * @brief Elimina todos los elementos de la lista.
     *
     * Reinicia el tamaño y la posición a cero.
     */
    void clear() {
        size = pos = 0;
    }

    /**
     * @brief Establece la posición actual al inicio de la lista.
     */
    void goToStart() {
        pos = 0;
    }

    /**
     * @brief Establece la posición actual al final de la lista (después del último elemento).
     */
    void goToEnd() {
        pos = size;
    }

    /**
     * @brief Establece la posición actual a una posición específica.
     *
     * @param pos Nueva posición a establecer.
     * @throws runtime_error Si la posición está fuera de los límites de la lista.
     */
    void goToPos(int pos) {
        if (pos < 0 || pos > size)
            throw runtime_error("Index out of bounds.");
        this->pos = pos;
    }

    /**
     * @brief Avanza la posición actual al siguiente elemento.
     *
     * Si la posición actual es menor que el tamaño, se incrementa en uno.
     */
    void next() {
        if (pos < size)
            pos++;
    }

    /**
     * @brief Retrocede la posición actual al elemento anterior.
     *
     * Si la posición actual es mayor que cero, se decrementa en uno.
     */
    void previous() {
        if (pos > 0)
            pos--;
    }

    /**
     * @brief Determina si la posición actual es el inicio de la lista.
     *
     * @return true si la posición actual es 0, false en caso contrario.
     */
    bool atStart() {
        return pos == 0;
    }

    /**
     * @brief Determina si la posición actual es el final de la lista.
     *
     * @return true si la posición actual es igual al tamaño de la lista, false en caso contrario.
     */
    bool atEnd() {
        return pos == size;
    }

    /**
     * @brief Retorna la posición actual en la lista.
     *
     * @return La posición actual.
     */
    int getPos() {
        return pos;
    }

    /**
     * @brief Retorna el número de elementos en la lista.
     *
     * @return El tamaño de la lista.
     */
    int getSize() {
        return size;
    }

    /**
     * @brief Busca el índice de un elemento en la lista a partir de una posición inicial.
     *
     * @param element Elemento a buscar.
     * @param start Posición desde la cual iniciar la búsqueda (por defecto 0).
     * @return El índice del elemento si se encuentra; de lo contrario, -1.
     * @throws runtime_error Si la posición de inicio está fuera de los límites.
     */
    int indexOf(E element, int start = 0) {
        if (start < 0 || start >= size)
            throw runtime_error("Index out of bounds.");
        for (int i = start; i < size; i++)
            if (elements[i] == element)
                return i;
        return -1;
    }

    /**
     * @brief Determina si la lista contiene un elemento específico.
     *
     * @param element Elemento a buscar.
     * @return true si el elemento está presente, false en caso contrario.
     */
    bool contains(E element) {
        return indexOf(element, 0) != -1;
    }

    /**
     * @brief Invierte el orden de los elementos de la lista.
     *
     * Crea un nuevo arreglo con los elementos en orden inverso y reemplaza el arreglo actual.
     */
    void reverse() {
        E* newElements = new E[max];
        for (int i = 0; i < size; i++)
            newElements[i] = elements[size - i - 1];
        delete[] elements;
        elements = newElements;
    }

    /**
     * @brief Compara la lista actual con otra lista para determinar si son iguales.
     *
     * Dos listas son iguales si tienen el mismo tamaño y los elementos en cada posición son idénticos.
     *
     * @param other Puntero a otra lista que implementa la interfaz List.
     * @return true si las listas son iguales, false en caso contrario.
     */
    bool equals(List<E>* other) {
        if (size != other->getSize())
            return false;
        for (int i = 0; i < size; i++)
            if (elements[i] != other->getElement())
                return false;
        return true;
    }

    /**
     * @brief Imprime el contenido de la lista.
     *
     * Muestra los elementos en el formato [ elem1, elem2, ... ]. Se indica la
     * posición actual con un asterisco (*) antes del elemento correspondiente.
     */
    void print() {
        cout << "[ ";
        for (int i = 0; i < size; i++) {
            if (i == pos)
                cout << "*";
            cout << elements[i];
            if (i < size - 1)
                cout << ", ";
            else 
                cout << " ";
        }
        if (pos == size)
            cout << "*";
        cout << "]" << endl;
    }

    /**
     * @brief Extiende la lista actual agregando los elementos de otra lista.
     *
     * Los elementos de la otra lista se agregan al final de la lista actual.
     *
     * @param other Puntero a la otra lista que implementa la interfaz List.
     */
    void extend(List<E>* other) {
        for (int i = 0; i < other->getSize(); i++)
            append(other->getElement());
    }
};
