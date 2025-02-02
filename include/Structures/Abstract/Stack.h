/**
 * @file Stack.h
 * @brief Interfaz para una pila (Stack) genérica.
 *
 * Esta interfaz define los métodos básicos para una estructura de pila,
 * incluyendo operaciones como apilar, desapilar y consultar elementos.
 *
 * @author Profesor Mauricio Aviles Cisneros
 */

#pragma once

/**
 * @brief Interfaz para una pila (Stack) genérica.
 *
 * Esta clase abstracta define la interfaz para una estructura de pila,
 * incluyendo métodos para apilar, desapilar y consultar elementos. Las clases
 * derivadas deben implementar estos métodos para proporcionar un comportamiento
 * concreto.
 *
 * @tparam E Tipo de dato almacenado en la pila.
 */
template <typename E>
class Stack {
private:
    /**
     * @brief Constructor de copia protegido.
     *
     * Se declara privado para evitar la copia de instancias de Stack.
     *
     * @param other Otra instancia de Stack.
     */
    Stack(const Stack<E>& other) {} // Constructor de copia protegido

    /**
     * @brief Operador de asignación protegido.
     *
     * Se declara privado para evitar la asignación de instancias de Stack.
     *
     * @param other Otra instancia de Stack.
     */
    void operator=(const Stack<E>& other) {} // Operador de asignación protegido

public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa una pila vacía.
     */
    Stack() {}

    /**
     * @brief Destructor virtual.
     *
     * Permite la correcta liberación de recursos en clases derivadas.
     */
    virtual ~Stack() {}

    /**
     * @brief Inserta un elemento en la cima de la pila.
     *
     * @param element Elemento a insertar.
     */
    virtual void push(E element) = 0;

    /**
     * @brief Elimina y retorna el elemento en la cima de la pila.
     *
     * @return El elemento eliminado de la cima.
     */
    virtual E pop() = 0;

    /**
     * @brief Retorna el elemento en la cima de la pila sin eliminarlo.
     *
     * @return El elemento en la cima de la pila.
     */
    virtual E topValue() = 0;

    /**
     * @brief Elimina todos los elementos de la pila.
     *
     * Limpia la pila, dejándola vacía.
     */
    virtual void clear() = 0;

    /**
     * @brief Verifica si la pila está vacía.
     *
     * @return true si la pila no contiene elementos, false en caso contrario.
     */
    virtual bool isEmpty() = 0;

    /**
     * @brief Retorna el número de elementos en la pila.
     *
     * @return La cantidad de elementos en la pila.
     */
    virtual int getSize() = 0;

    /**
     * @brief Imprime el contenido de la pila.
     *
     * Este método debe ser implementado para mostrar el estado de la pila.
     */
    virtual void print() = 0;
};