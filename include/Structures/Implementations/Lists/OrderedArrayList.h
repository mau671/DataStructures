/**
 * @file OrderedArrayList.h
 * @brief Implementación de una lista ordenada utilizando un ArrayList.
 * 
 * Proporciona operaciones de inserción, eliminación, búsqueda y manipulación de elementos.
 * 
 * @author Profesor Mauricio Aviles Cisneros
 * @author Mauricio González Prendas
 */

#pragma once

#include "Structures/Implementations/Lists/ArrayList.h"

/**
 * @brief Clase que implementa una lista ordenada utilizando composición de un ArrayList.
 *
 * Esta clase mantiene los elementos en orden ascendente. Para insertar un nuevo elemento,
 * se recorre la lista hasta encontrar la posición correcta de acuerdo al orden, y se inserta allí.
 *
 * @tparam E Tipo de dato almacenado en la lista.
 */
template <typename E>
class OrderedArrayList : public List<E> {
private:
    List<E>* data; ///< Puntero a la lista subyacente que almacena los elementos.

public:
    /**
     * @brief Constructor que inicializa la lista ordenada con una capacidad máxima.
     *
     * @param max Capacidad máxima inicial para la lista. Por defecto, DEFAULT_MAX.
     */
    OrderedArrayList(int max = DEFAULT_MAX) {
        data = new ArrayList<E>(max);
    }

    /**
     * @brief Destructor que libera la memoria utilizada por la lista.
     */
    ~OrderedArrayList() {
        delete data;
    }

    /**
     * @brief Inserta un elemento en la posición correcta para mantener el orden ascendente.
     *
     * Se recorre la lista desde el inicio hasta encontrar el lugar en el que el elemento
     * es menor que o igual al elemento actual, y se inserta en esa posición.
     *
     * @param element Elemento a insertar.
     */
    void insert(E element) {
        data->goToStart();
        while (!data->atEnd() && element >= data->getElement())
            data->next();
        data->insert(element);
    }

    /**
     * @brief Agrega un elemento a la lista ordenada.
     *
     * Este método es equivalente a llamar a insert, ya que la lista siempre se mantiene ordenada.
     *
     * @param element Elemento a agregar.
     */
    void append(E element) {
        insert(element);
    }

    /**
     * @brief Elimina y retorna el elemento en la posición actual de la lista.
     *
     * @return El elemento eliminado.
     */
    E remove() {
        return data->remove();
    }

    /**
     * @brief Obtiene el elemento en la posición actual de la lista.
     *
     * @return El elemento actual.
     */
    E getElement() {
        return data->getElement();
    }

    /**
     * @brief Elimina todos los elementos de la lista.
     */
    void clear() {
        data->clear();
    }

    /**
     * @brief Establece la posición actual al inicio de la lista.
     */
    void goToStart() {
        data->goToStart();
    }

    /**
     * @brief Establece la posición actual al final de la lista (después del último elemento).
     */
    void goToEnd() {
        data->goToEnd();
    }

    /**
     * @brief Establece la posición actual a una posición específica.
     *
     * @param pos Posición a la que se desea mover el cursor.
     */
    void goToPos(int pos) {
        data->goToPos(pos);
    }

    /**
     * @brief Avanza la posición actual al siguiente elemento.
     */
    void next() {
        data->next();
    }

    /**
     * @brief Retrocede la posición actual al elemento anterior.
     */
    void previous() {
        data->previous();
    }

    /**
     * @brief Determina si la posición actual es el inicio de la lista.
     *
     * @return true si la posición actual es 0, false en caso contrario.
     */
    bool atStart() {
        return data->atStart();
    }

    /**
     * @brief Determina si la posición actual es el final de la lista.
     *
     * @return true si la posición actual es igual al tamaño de la lista, false en caso contrario.
     */
    bool atEnd() {
        return data->atEnd();
    }

    /**
     * @brief Retorna la posición actual en la lista.
     *
     * @return La posición actual.
     */
    int getPos() {
        return data->getPos();
    }

    /**
     * @brief Retorna el número de elementos en la lista.
     *
     * @return El tamaño de la lista.
     */
    int getSize() {
        return data->getSize();
    }

    /**
     * @brief Busca el índice de un elemento en la lista a partir de una posición inicial.
     *
     * @param element Elemento a buscar.
     * @param start Posición desde la cual iniciar la búsqueda (por defecto 0).
     * @return El índice del elemento si se encuentra; de lo contrario, -1.
     */
    int indexOf(E element, int start = 0) {
        return data->indexOf(element, start);
    }

    /**
     * @brief Determina si la lista contiene un elemento específico.
     *
     * @param element Elemento a buscar.
     * @return true si el elemento está presente, false en caso contrario.
     */
    bool contains(E element) {
        return data->contains(element);
    }

    /**
     * @brief Invierte el orden de los elementos en la lista.
     */
    void reverse() {
        data->reverse();
    }

    /**
     * @brief Compara la lista actual con otra lista para determinar si son iguales.
     *
     * @param other Puntero a otra lista que implementa la interfaz List.
     * @return true si las listas son iguales, false en caso contrario.
     */
    bool equals(List<E>* other) {
        return data->equals(other);
    }

    /**
     * @brief Extiende la lista actual agregando los elementos de otra lista.
     *
     * @param other Puntero a la otra lista que implementa la interfaz List.
     */
    void extend(List<E>* other) {
        data->extend(other);
    }

    /**
     * @brief Modifica el elemento en la posición actual de la lista.
     *
     * @param element Nuevo valor a asignar.
     */
    void set(E element) {
        data->set(element);
    }

    /**
     * @brief Imprime los elementos de la lista en la consola.
     */
    void print() {
        data->print();
    }
};
