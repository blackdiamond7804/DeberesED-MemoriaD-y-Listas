#include "Nodo.h"
#include<string>

using namespace std;

template <typename T>
Nodo<T>::Nodo(T _dato) {
    dato = _dato;
    siguiente = nullptr;
    anterior = nullptr;
}

template <typename T>
void Nodo<T>::setDato(T _dato) {
    dato = _dato;
}

template <typename T>
void Nodo<T>::setSiguiente(Nodo* _siguiente) {
    siguiente = _siguiente;
}

template <typename T>
void Nodo<T>::setAnterior(Nodo* _anterior) {
    anterior = _anterior;
}

template <typename T>
T Nodo<T>::getDato() {
    return dato;
}

template <typename T>
Nodo<T>* Nodo<T>::getSiguiente() {
    return siguiente;
}

template <typename T>
Nodo<T>* Nodo<T>::getAnterior() {
    return anterior;
}

// Explicit template instantiation
template class Nodo<int>;
template class Nodo<float>;
template class Nodo<double>;
template class Nodo<string>;
