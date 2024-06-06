#include "ListasCirculares.h"
#include <iostream>
using namespace std;

template<typename T>
ListaCircular<T>::ListaCircular() {
    primero = nullptr;
    ultimo = nullptr;
    tamano = 0;
}

template<typename T>
ListaCircular<T>::~ListaCircular() {
    if (primero != nullptr) {
        Nodo<T>* actual = primero;
        Nodo<T>* siguiente;
        do {
            siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        } while (actual != primero);
    }
}

template<typename T>
void ListaCircular<T>::Insertar(T dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (primero == nullptr) {
        primero = nuevo;
        primero->setSiguiente(primero);
        ultimo = primero;
    }
    else {
        ultimo->setSiguiente(nuevo);
        nuevo->setSiguiente(primero);
        ultimo = nuevo;
    }
    tamano++;
}

template<typename T>
void ListaCircular<T>::Buscar(T dato) {
    if (primero != nullptr) {
        Nodo<T>* actual = primero;
        bool encontrado = false;
        do {
            if (actual->getDato() == dato) {
                cout << "El elemento " << dato << " ha sido encontrado en la lista" << endl;
                encontrado = true;
                break;
            }
            actual = actual->getSiguiente();
        } while (actual != primero);
        if (!encontrado) {
            cout << "El elemento " << dato << " no ha sido encontrado en la lista" << endl;
        }
    }
    else {
        cout << "La lista se encuentra vacia" << endl;
    }
}

template<typename T>
void ListaCircular<T>::Eliminar(T dato) {
    if (primero != nullptr) {
        Nodo<T>* actual = primero;
        Nodo<T>* anterior = nullptr;
        bool encontrado = false;
        do {
            if (actual->getDato() == dato) {
                if (actual == primero) {
                    primero = primero->getSiguiente();
                    ultimo->setSiguiente(primero);
                }
                else if (actual == ultimo) {
                    anterior->setSiguiente(primero);
                    ultimo = anterior;
                }
                else {
                    anterior->setSiguiente(actual->getSiguiente());
                }
                delete actual;
                tamano--;
                cout << "El elemento " << dato << " ha sido eliminado de la lista" << endl;
                encontrado = true;
                break;
            }
            anterior = actual;
            actual = actual->getSiguiente();
        } while (actual != primero);
        if (!encontrado) {
            cout << "El elemento " << dato << " no ha sido encontrado en la lista" << endl;
        }
    }
    else {
        cout << "La lista se encuentra vacia" << endl;
    }
}

template<typename T>
void ListaCircular<T>::Mostrar() {
    if (primero != nullptr) {
        Nodo<T>* actual = primero;
        do {
            cout << actual->getDato() << " -> ";
            actual = actual->getSiguiente();
        } while (actual != primero);
        cout << "Primero" << endl;
    }
    else {
        cout << "La lista se encuentra vacia" << endl;
    }
}

template<typename T>
int ListaCircular<T>::Tamano() {
    return tamano;
}

// Explicit instantiation
template class ListaCircular<int>;