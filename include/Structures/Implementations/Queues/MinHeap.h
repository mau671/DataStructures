/**
 * @file MinHeap.h
 * @brief Este archivo contiene la implementación de la clase MinHeap, que representa un heap mínimo.
 * 
 * @author Profesor Mauricio Aviles Cisneros
 */

#pragma once

#define DEFAULT_MAX 1024

#include <stdexcept>
#include <iostream>
#include <cmath>

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @class MinHeap
 * @brief Clase que implementa un heap mínimo.
 * 
 * Un heap mínimo es una estructura de datos en la que el elemento más pequeño siempre está en la raíz.
 * Esta clase permite insertar elementos, eliminar el elemento mínimo, y realizar otras operaciones básicas.
 * 
 * @tparam E Tipo de los elementos almacenados en el heap.
 */
template <typename E>
class MinHeap {
private:
    E* elements; ///< Arreglo que almacena los elementos del heap.
    int max;     ///< Capacidad máxima del heap.
    int size;    ///< Número actual de elementos en el heap.

    /**
     * @brief Realiza un sift-up para mantener la propiedad del heap.
     * 
     * @param pos Posición del elemento a mover hacia arriba.
     */
    void siftUp(int pos) {
        while (pos != 0 && elements[pos] < elements[parent(pos)]) {
            swap(pos, parent(pos));
            pos = parent(pos);
        }
    }

    /**
     * @brief Realiza un sift-down para mantener la propiedad del heap.
     * 
     * @param pos Posición del elemento a mover hacia abajo.
     */
    void siftDown(int pos) {
        while (!isLeaf(pos) && elements[pos] > elements[minChild(pos)]) {
            int mChild = minChild(pos);
            swap(pos, mChild);
            pos = mChild;
        }
    }

    /**
     * @brief Obtiene la posición del padre de un nodo.
     * 
     * @param pos Posición del nodo.
     * @return Posición del padre.
     */
    int parent(int pos) {
        return (pos - 1) / 2;
    }

    /**
     * @brief Obtiene la posición del hijo izquierdo de un nodo.
     * 
     * @param pos Posición del nodo.
     * @return Posición del hijo izquierdo.
     */
    int leftChild(int pos) {
        return 2 * pos + 1;
    }

    /**
     * @brief Obtiene la posición del hijo derecho de un nodo.
     * 
     * @param pos Posición del nodo.
     * @return Posición del hijo derecho.
     */
    int rightChild(int pos) {
        return 2 * pos + 2;
    }

    /**
     * @brief Verifica si un nodo es una hoja.
     * 
     * @param pos Posición del nodo.
     * @return true si el nodo es una hoja, false en caso contrario.
     */
    bool isLeaf(int pos) {
        return leftChild(pos) >= size;
    }

    /**
     * @brief Intercambia dos elementos en el heap.
     * 
     * @param pos1 Posición del primer elemento.
     * @param pos2 Posición del segundo elemento.
     */
    void swap(int pos1, int pos2) {
        E temp = elements[pos1];
        elements[pos1] = elements[pos2];
        elements[pos2] = temp;
    }

    /**
     * @brief Obtiene la posición del hijo con el valor mínimo.
     * 
     * @param pos Posición del nodo.
     * @return Posición del hijo con el valor mínimo.
     */
    int minChild(int pos) {
        if (rightChild(pos) >= size || elements[leftChild(pos)] < elements[rightChild(pos)])
            return leftChild(pos);
        return rightChild(pos);
    }

public:
    /**
     * @brief Constructor de la clase MinHeap.
     * 
     * @param max Capacidad máxima del heap.
     * @throw runtime_error Si la capacidad máxima es menor que 1.
     */
    MinHeap(int max = DEFAULT_MAX) {
        if (max < 1)
            throw runtime_error("Invalid max size.");
        elements = new E[max];
        size = 0;
        this->max = max;
    }

    /**
     * @brief Destructor de la clase MinHeap.
     */
    ~MinHeap() {
        delete[] elements;
    }

    /**
     * @brief Inserta un elemento en el heap.
     * 
     * @param element Elemento a insertar.
     * @throw runtime_error Si el heap está lleno.
     */
    void insert(E element) {
        if (size == max)
            throw runtime_error("Heap is full.");
        elements[size] = element;
        size++;
        siftUp(size - 1);
    }

    /**
     * @brief Obtiene el primer elemento del heap (el mínimo).
     * 
     * @return El elemento mínimo.
     * @throw runtime_error Si el heap está vacío.
     */
    E first() {
        if (size == 0)
            throw runtime_error("Heap is empty.");
        return elements[0];
    }

    /**
     * @brief Elimina y devuelve el primer elemento del heap (el mínimo).
     * 
     * @return El elemento mínimo.
     * @throw runtime_error Si el heap está vacío.
     */
    E removeFirst() {
        return remove(0);
    }

    /**
     * @brief Elimina y devuelve un elemento en una posición específica.
     * 
     * @param pos Posición del elemento a eliminar.
     * @return El elemento eliminado.
     * @throw runtime_error Si la posición está fuera de los límites.
     */
    E remove(int pos) {
        if (pos < 0 || pos >= size)
            throw runtime_error("Index out of bounds.");

        swap(pos, size - 1);
        size--;
        siftDown(pos);
        return elements[size];
    }

    /**
     * @brief Limpia el heap, eliminando todos los elementos.
     */
    void clear() {
        size = 0;
    }

    /**
     * @brief Verifica si el heap está vacío.
     * 
     * @return true si el heap está vacío, false en caso contrario.
     */
    bool isEmpty() {
        return size == 0;
    }

    /**
     * @brief Obtiene el número de elementos en el heap.
     * 
     * @return Número de elementos en el heap.
     */
    int getSize() {
        return size;
    }

    /**
     * @brief Imprime el contenido del heap como si fuera un árbol.
     */
    void print() {
        cout << "[ ";
        for (int i = 0; i < size; i++) {
            cout << elements[i];
            if (i != size - 1) {
                cout << ", ";
            }
        }
        cout << " ]";
        cout << endl;
    }

    /**
     * @brief Obtiene un elemento en una posición específica.
     * 
     * @param index Posición del elemento.
     * @return El elemento en la posición especificada.
     * @throw runtime_error Si la posición está fuera de los límites.
     */
    E get(int index) {
        if (index < 0 || index >= size) {
            throw runtime_error("Index out of bounds.");
        }
        return elements[index];
    }
};