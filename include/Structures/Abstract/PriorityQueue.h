/*
 * Archivo: PriorityQueue.h
 * Descripción: Interfaz de una cola de prioridad genérica. 
 *
 * Autor(es): Profesor Mauricio Aviles Cisneros
 */

#pragma once

/**
 * @brief Interfaz para una cola de prioridad genérica.
 *
 * Esta interfaz define los métodos básicos para una cola de prioridad, que permiten insertar
 * elementos con una prioridad asociada, obtener el elemento con la mínima prioridad, eliminar
 * dicho elemento, y gestionar el estado de la cola.
 *
 * @tparam E Tipo de dato almacenado en la cola de prioridad.
 */
template <typename E>
class PriorityQueue {
private:
    /**
     * @brief Constructor de copia privado.
     *
     * Se declara privado para evitar la copia de instancias de PriorityQueue.
     *
     * @param other Otra instancia de PriorityQueue.
     */
    PriorityQueue(const PriorityQueue<E>& other) {}

    /**
     * @brief Operador de asignación privado.
     *
     * Se declara privado para evitar la asignación de instancias de PriorityQueue.
     *
     * @param other Otra instancia de PriorityQueue.
     */
    void operator =(const PriorityQueue<E>& other) {}

public:
    /**
     * @brief Constructor por defecto.
     */
    PriorityQueue() {}

    /**
     * @brief Destructor virtual.
     */
    virtual ~PriorityQueue() {}

    /**
     * @brief Inserta un elemento en la cola de prioridad.
     *
     * Inserta el elemento con la prioridad especificada.
     *
     * @param element Elemento a insertar.
     * @param priority Prioridad asociada al elemento.
     */
    virtual void insert(E element, int priority) = 0;

    /**
     * @brief Obtiene el elemento con la mínima prioridad.
     *
     * @return El elemento con la mínima prioridad.
     */
    virtual E min() = 0;

    /**
     * @brief Elimina y retorna el elemento con la mínima prioridad.
     *
     * @return El elemento eliminado que tenía la mínima prioridad.
     */
    virtual E removeMin() = 0;

    /**
     * @brief Elimina todos los elementos de la cola.
     */
    virtual void clear() = 0;

    /**
     * @brief Retorna el número de elementos en la cola.
     *
     * @return La cantidad de elementos actualmente en la cola.
     */
    virtual int getSize() = 0;

    /**
     * @brief Determina si la cola está vacía.
     *
     * @return true si la cola no contiene elementos, false en caso contrario.
     */
    virtual bool isEmpty() = 0;

    /**
     * @brief Imprime el contenido de la cola de prioridad.
     */
    virtual void print() = 0;
};
