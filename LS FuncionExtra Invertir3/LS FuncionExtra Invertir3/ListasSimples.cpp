#include "ListasSimples.h"

template <typename T>
inline ListaSimples<T>::ListaSimples() {
    cabeza = NULL;
}

template <typename T>
inline void ListaSimples<T>::Insertar(T _dato) {
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
    }
    else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != NULL) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
}

template <typename T>
inline void ListaSimples<T>::Buscar(T _dato) {
    auto buscar = [&](Nodo<T>* nodo) -> bool {
        return nodo->getDato() == _dato;
        };

    Nodo<T>* aux = cabeza;
    while (aux != NULL) {
        if (buscar(aux)) {
            cout << "El dato " << _dato << " si se encuentra en la lista" << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}

template <typename T>
inline void ListaSimples<T>::Eliminar(T _dato) {
    Nodo<T>* aux = cabeza;
    Nodo<T>* anterior = NULL;
    while (aux != NULL) {
        if (aux->getDato() == _dato) {
            if (anterior == NULL) {
                cabeza = aux->getSiguiente();
            }
            else {
                anterior->setSiguiente(aux->getSiguiente());
            }
            delete aux;
            cout << "El dato " << _dato << " se ha eliminado de la lista" << endl;
            return;
        }
        anterior = aux;
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}

template <typename T>
inline void ListaSimples<T>::Mostrar() {
    auto mostrar = [](Nodo<T>* nodo) {
        cout << nodo->getDato() << " -> ";
        };

    Nodo<T>* aux = cabeza;
    while (aux != NULL) {
        mostrar(aux);
        aux = aux->getSiguiente();
    }
    cout << "NULL" << endl;
}

template <typename T>
inline void ListaSimples<T>::Invertir() {
    Nodo<T>* anterior = NULL;
    Nodo<T>* actual = cabeza;
    Nodo<T>* siguiente = NULL;
    while (actual != NULL) {
        siguiente = actual->getSiguiente(); // Guarda el siguiente nodo
        actual->setSiguiente(anterior); // Invierte el puntero del nodo actual
        anterior = actual; // Mueve 'anterior' al nodo actual
        actual = siguiente; // Avanza 'actual' al siguiente nodo
    }
    cabeza = anterior; // Actualiza la cabeza para que apunte al nuevo primer nodo
    cout << "La lista ha sido invertida." << endl;
    Mostrar(); // Muestra la lista invertida
}

// Explicit template instantiation
template class ListaSimples<int>;
template class ListaSimples<string>;
