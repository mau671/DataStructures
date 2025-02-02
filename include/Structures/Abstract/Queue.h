/**
 * @file Queue.h
 * @brief Interfaz para una cola genérica.
 *
 * Esta interfaz define los métodos básicos para una estructura de cola, incluyendo operaciones
 * estándar como insertar, eliminar y consultar elementos. Además, se incluyen métodos adicionales
 * para soportar operaciones de doble extremo (Deque).
 *
 * @author Profesor Mauricio Aviles Cisneros
 */

#pragma once

/**
 * @brief Interfaz para una cola genérica.
 *
 * Esta clase abstracta define la interfaz básica para una estructura de cola,
 * incluyendo métodos para operaciones estándar como insertar, eliminar y
 * consultar elementos. Además, se incluyen métodos adicionales para soportar
 * operaciones de doble extremo (Deque). Las clases derivadas deben implementar
 * estos métodos para proporcionar un comportamiento concreto.
 *
 * @tparam E Tipo de dato almacenado en la cola.
 */
template <typename E>
class Queue {
private:
    /**
     * @brief Constructor de copia protegido.
     *
     * Se declara privado para evitar la copia de instancias de Queue.
     *
     * @param other Otra instancia de Queue.
     */
    Queue(const Queue<E>& other) {} // Protect copy constructor

    /**
     * @brief Operador de asignación protegido.
     *
     * Se declara privado para evitar la asignación de instancias de Queue.
     *
     * @param other Otra instancia de Queue.
     */
    void operator=(const Queue<E>& other) {} // Protect assignment operator

public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa una cola vacía.
     */
    Queue() {} // Default constructor

    /**
     * @brief Destructor virtual.
     *
     * Permite la correcta liberación de recursos en clases derivadas.
     */
    virtual ~Queue() {} // Base destructor

    // Métodos originales de la clase Queue

    /**
     * @brief Inserta un elemento al final de la cola.
     *
     * @param element Elemento a insertar.
     */
    virtual void enqueue(E element) = 0; // Insertar un elemento al final de la cola

    /**
     * @brief Elimina y retorna el elemento que se encuentra al frente de la cola.
     *
     * @return El elemento eliminado.
     */
    virtual E dequeue() = 0; // Eliminar y retornar el elemento al frente de la cola

    /**
     * @brief Retorna el elemento que se encuentra al frente de la cola sin eliminarlo.
     *
     * @return El elemento en el frente de la cola.
     */
    virtual E frontValue() = 0; // Retornar el elemento en el frente de la cola

    /**
     * @brief Remueve todos los elementos de la cola.
     *
     * Limpia la cola, dejándola vacía.
     */
    virtual void clear() = 0; // Remover todos los elementos de la cola

    /**
     * @brief Determina si la cola está vacía.
     *
     * @return true si la cola no contiene elementos, false en caso contrario.
     */
    virtual bool isEmpty() = 0; // Retornar true si la cola está vacía

    /**
     * @brief Retorna el número de elementos actualmente en la cola.
     *
     * @return La cantidad de elementos en la cola.
     */
    virtual int getSize() = 0; // Retornar el número de elementos en la cola

    /**
     * @brief Imprime el contenido de la cola.
     *
     * Este método debe ser implementado para mostrar el estado de la cola.
     */
    virtual void print() = 0; // Imprimir la cola

    // Nuevos métodos para soporte de Deque

    /**
     * @brief Inserta un elemento al frente de la cola.
     *
     * @param element Elemento a insertar en la parte frontal.
     */
    virtual void enqueueFront(E element) = 0; // Insertar un elemento al frente de la cola

    /**
     * @brief Elimina y retorna el elemento que se encuentra al final de la cola.
     *
     * @return El elemento eliminado del final de la cola.
     */
    virtual E dequeueBack() = 0; // Eliminar y retornar el elemento al final de la cola

    /**
     * @brief Retorna el elemento que se encuentra al final de la cola sin eliminarlo.
     *
     * @return El elemento en el final de la cola.
     */
    virtual E backValue() = 0; // Retornar el elemento en el final de la cola
};