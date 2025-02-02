/*
 * Archivo: KVPair.h
 * Descripción: Clase que representa un par clave-valor genérico.
 *              Proporciona métodos para la comparación de pares y sobrecarga 
 *              de operadores para facilitar su uso en contenedores.
 *
 * Autor(es): Profesor Mauricio Aviles Cisneros
 */

#pragma once
#include <iostream>

using std::ostream;

template <typename K, typename V>
class KVPair {
public:
    K key;    ///< La clave del par.
    V value;  ///< El valor asociado a la clave.

    /** 
     * @brief Constructor por defecto.
     */
    KVPair() {}

    /** 
     * @brief Constructor que inicializa solo la clave.
     * 
     * @param key La clave a inicializar.
     */
    KVPair(K key) {
        this->key = key;
    }

    /** 
     * @brief Constructor que inicializa el par clave-valor.
     * 
     * @param key La clave a inicializar.
     * @param value El valor asociado a la clave.
     */
    KVPair(K key, V value) {
        this->key = key;
        this->value = value;
    }

    /** 
     * @brief Constructor de copia.
     * 
     * @param other El par clave-valor a copiar.
     */
    KVPair(const KVPair<K, V>& other) : key(other.key), value(other.value) {}

    /** 
     * @brief Operador de asignación.
     * 
     * @param other El par clave-valor a asignar.
     * @return Referencia a este objeto.
     */
    KVPair<K, V>& operator=(const KVPair<K, V>& other) {
        if (this != &other) { // Verifica la autoasignación
            this->key = other.key;
            this->value = other.value;
        }
        return *this;
    }

    /** 
     * @brief Comparador de igualdad.
     * 
     * @param other El par clave-valor a comparar.
     * @return true si las claves son iguales, false en caso contrario.
     */
    bool operator==(const KVPair<K, V>& other) const {
        return this->key == other.key;
    }

    /** 
     * @brief Comparador de desigualdad.
     * 
     * @param other El par clave-valor a comparar.
     * @return true si las claves son diferentes, false en caso contrario.
     */
    bool operator!=(const KVPair<K, V>& other) {
        return this->key != other.key;
    }

    /** 
     * @brief Comparador menor que.
     * 
     * @param other El par clave-valor a comparar.
     * @return true si la clave de este par es menor que la clave del otro par.
     */
    bool operator<(const KVPair<K, V>& other) {
        return this->key < other.key;
    }

    /** 
     * @brief Comparador menor o igual que.
     * 
     * @param other El par clave-valor a comparar.
     * @return true si la clave de este par es menor o igual que la clave del otro par.
     */
    bool operator<=(const KVPair<K, V>& other){
        return this->key <= other.key;
    }

    /** 
     * @brief Comparador mayor que.
     * 
     * @param other El par clave-valor a comparar.
     * @return true si la clave de este par es mayor que la clave del otro par.
     */
    bool operator>(const KVPair<K, V>& other) {
        return this->key > other.key;
    }

    /** 
     * @brief Comparador mayor o igual que.
     * 
     * @param other El par clave-valor a comparar.
     * @return true si la clave de este par es mayor o igual que la clave del otro par.
     */
    bool operator>=(const KVPair<K, V>& other) {
        return this->key >= other.key;
    }
};

/** 
 * @brief Sobrecarga del operador de salida para imprimir un par clave-valor.
 * 
 * @param os Flujo de salida.
 * @param pair El par clave-valor a imprimir.
 * @return Referencia al flujo de salida.
 */
template <typename K, typename V>
ostream& operator<<(ostream& os, const KVPair<K, V>& pair) {
    os << "(" << pair.key << ", " << pair.value << ")";
    return os;
}
