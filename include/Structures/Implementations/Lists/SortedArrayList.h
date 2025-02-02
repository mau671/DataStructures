/**
 * @file SortedArrayList.h
 * @brief Implementación de una lista ordenada utilizando un arreglo dinámico.
 * 
 * Proporciona operaciones de inserción y agregación de elementos, manteniendo el orden ascendente.
 * 
 * @author Profesor Mauricio Aviles Cisneros
 * @author Mauricio González Prendas
 */

#pragma once

#include "Structures/Implementations/Lists/ArrayList.h"

/**
 * @brief Clase que implementa una lista ordenada mediante herencia,
 *        especializando la clase ArrayList.
 *
 * Esta clase mantiene los elementos en orden ascendente. La inserción
 * se realiza recorriendo la lista hasta encontrar la posición correcta,
 * garantizando que el arreglo se mantenga ordenado.
 *
 * @tparam E Tipo de dato almacenado en la lista.
 */
template <typename E>
class SortedArrayList : public ArrayList<E> {
public:
    /**
     * @brief Constructor que inicializa la lista ordenada con una capacidad máxima.
     *
     * @param max Capacidad máxima inicial para la lista. Por defecto, DEFAULT_MAX.
     */
    SortedArrayList(int max = DEFAULT_MAX) : ArrayList<E>(max) {}

    /**
     * @brief Inserta un elemento en la posición adecuada para mantener el orden ascendente.
     *
     * Recorre la lista desde el inicio hasta encontrar la posición en la que el nuevo elemento
     * es menor que el elemento actual, y lo inserta en ese punto.
     *
     * @param element Elemento a insertar.
     */
    void insert(E element) {
        ArrayList<E>::goToStart();
        while (!ArrayList<E>::atEnd() && element >= ArrayList<E>::getElement())
            ArrayList<E>::next();
        ArrayList<E>::insert(element);
    }

    /**
     * @brief Agrega un elemento a la lista ordenada.
     *
     * Este método es equivalente a llamar a insert(), ya que la lista
     * se mantiene ordenada automáticamente.
     *
     * @param element Elemento a agregar.
     */
    void append(E element) {
        insert(element);
    }
};
