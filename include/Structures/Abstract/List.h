/*
 * Archivo: List.h
 * Descripción: Clase abstracta que define la interfaz para una lista genérica.
 *              Permite insertar, eliminar y manipular elementos en una lista.
 *
 * Autor(es):  Profesor Mauricio Aviles Cisneros, Mauricio González Prendas
 */

#pragma once

/**
 * @brief Clase abstracta que define la interfaz para una lista genérica.
 *
 * Esta clase representa una lista que almacena elementos de tipo E. 
 * Las implementaciones concretas de esta clase deberán definir el 
 * comportamiento de los métodos para manipular la lista.
 *
 * @tparam E Tipo de los elementos almacenados en la lista.
 */
template <typename E>
class List {
private:
	// Constructor de copia privado para evitar copias no deseadas.
	List(const List<E>& other) {}

	// Operador de asignación privado para evitar asignaciones no deseadas.
	void operator =(const List<E>& other) {}

public:
	/** 
	 * @brief Constructor por defecto.
	 * 
	 * Inicializa una lista vacía.
	 */
	List() {}

	/** 
	 * @brief Destructor virtual.
	 * 
	 * Asegura que los recursos se liberen correctamente en las clases derivadas.
	 */
	virtual ~List() {}

	/**
	 * @brief Inserta un elemento al principio de la lista.
	 *
	 * @param element El elemento a insertar.
	 */
	virtual void insert(E element) = 0;

	/**
	 * @brief Agrega un elemento al final de la lista.
	 *
	 * @param element El elemento a añadir.
	 */
	virtual void append(E element) = 0;

	/**
	 * @brief Establece el elemento en la posición actual.
	 *
	 * @param element El nuevo elemento a establecer.
	 */
	virtual void set(E element) = 0;

	/**
	 * @brief Elimina y devuelve el elemento en la parte superior de la lista.
	 *
	 * @return El elemento que fue eliminado.
	 */
	virtual E remove() = 0;

	/**
	 * @brief Recupera el elemento en la posición actual.
	 *
	 * @return El elemento en la posición actual.
	 */
	virtual E getElement() = 0;

	/**
	 * @brief Limpia todos los elementos de la lista.
	 */
	virtual void clear() = 0;

	/**
	 * @brief Mueve el cursor al inicio de la lista.
	 */
	virtual void goToStart() = 0;

	/**
	 * @brief Mueve el cursor al final de la lista.
	 */
	virtual void goToEnd() = 0;

	/**
	 * @brief Mueve el cursor a una posición específica.
	 *
	 * @param pos La posición a la que mover el cursor.
	 */
	virtual void goToPos(int pos) = 0;

	/**
	 * @brief Avanza el cursor a la siguiente posición.
	 */
	virtual void next() = 0;

	/**
	 * @brief Retrocede el cursor a la posición anterior.
	 */
	virtual void previous() = 0;

	/**
	 * @brief Verifica si el cursor está en la posición inicial.
	 *
	 * @return true si el cursor está en la posición inicial, false en caso contrario.
	 */
	virtual bool atStart() = 0;

	/**
	 * @brief Verifica si el cursor está en la posición final.
	 *
	 * @return true si el cursor está en la posición final, false en caso contrario.
	 */
	virtual bool atEnd() = 0;

	/**
	 * @brief Obtiene la posición actual del cursor.
	 *
	 * @return La posición actual del cursor.
	 */
	virtual int getPos() = 0;

	/**
	 * @brief Obtiene el número de elementos en la lista.
	 *
	 * @return El tamaño de la lista.
	 */
	virtual int getSize() = 0;

	/**
	 * @brief Imprime el contenido de la lista.
	 *
	 * Este método debe ser implementado para mostrar el estado de la lista.
	 */
	virtual void print() = 0;

	// Nuevos métodos añadidos a la interfaz de la lista

	/**
	 * @brief Busca el índice de un elemento en la lista comenzando desde una posición específica.
	 *
	 * @param element El elemento a buscar.
	 * @param start La posición desde donde comenzar la búsqueda.
	 * @return El índice del elemento si se encuentra, -1 en caso contrario.
	 */
	virtual int indexOf(E element, int start) = 0;

	/**
	 * @brief Verifica si la lista contiene un elemento específico.
	 *
	 * @param element El elemento a buscar.
	 * @return true si el elemento está en la lista, false en caso contrario.
	 */
	virtual bool contains(E element) = 0;

	/**
	 * @brief Invierte el orden de los elementos en la lista.
	 */
	virtual void reverse() = 0;

	/**
	 * @brief Compara esta lista con otra para verificar si son iguales.
	 *
	 * @param other La lista con la que se comparará.
	 * @return true si las listas son iguales, false en caso contrario.
	 */
	virtual bool equals(List<E>* other) = 0;

	/**
	 * @brief Extiende la lista actual agregando los elementos de otra lista.
	 *
	 * @param other La lista cuyos elementos se agregarán.
	 */
	virtual void extend(List<E>* other) = 0;
};
