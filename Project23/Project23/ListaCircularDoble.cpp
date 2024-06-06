#include "ListaCircularDoble.h"
#include <iostream>
using namespace std;

template <typename T>
ListaCircularDoble<T>::ListaCircularDoble()
{
    this->cabeza = nullptr;
    this->cola = nullptr;
}

template <typename T>
ListaCircularDoble<T>::~ListaCircularDoble()
{
    if (this->cabeza != nullptr) {
        NodoDoble<T>* actual = this->cabeza;
        do {
            NodoDoble<T>* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        } while (actual != this->cabeza);
    }
}

template <typename T>
void ListaCircularDoble<T>::insertar(T dato)
{
    NodoDoble<T>* nuevo = new NodoDoble<T>(dato);
    if (this->cabeza == nullptr)
    {
        this->cabeza = nuevo;
        this->cola = nuevo;
        this->cabeza->setSiguiente(this->cola);
        this->cabeza->setAnterior(this->cola);
        this->cola->setSiguiente(this->cabeza);
        this->cola->setAnterior(this->cabeza);
    }
    else
    {
        this->cola->setSiguiente(nuevo);
        nuevo->setAnterior(this->cola);
        nuevo->setSiguiente(this->cabeza);
        this->cabeza->setAnterior(nuevo);
        this->cola = nuevo;
    }
}

template <typename T>
void ListaCircularDoble<T>::eliminar(T dato)
{
    if (this->cabeza != nullptr)
    {
        if (this->cabeza->getDato() == dato)
        {
            NodoDoble<T>* aux = this->cabeza;
            this->cabeza = this->cabeza->getSiguiente();
            this->cabeza->setAnterior(this->cola);
            this->cola->setSiguiente(this->cabeza);
            delete aux;
        }
        else
        {
            NodoDoble<T>* aux = this->cabeza;
            while (aux->getSiguiente() != this->cabeza)
            {
                if (aux->getSiguiente()->getDato() == dato)
                {
                    NodoDoble<T>* aux2 = aux->getSiguiente();
                    aux->setSiguiente(aux2->getSiguiente());
                    aux2->getSiguiente()->setAnterior(aux);
                    delete aux2;
                    break;
                }
                aux = aux->getSiguiente();
            }
        }
    }
}

template <typename T>
void ListaCircularDoble<T>::mostrar(std::function<void(T)> printFunction)
{
    if (this->cabeza != nullptr)
    {
        NodoDoble<T>* aux = this->cabeza;
        do
        {
            printFunction(aux->getDato());
            aux = aux->getSiguiente();
        } while (aux != this->cabeza);
        cout << endl;
    }
}

template <typename T>
bool ListaCircularDoble<T>::buscar(T dato)
{
    if (this->cabeza != nullptr)
    {
        NodoDoble<T>* aux = this->cabeza;
        do
        {
            if (aux->getDato() == dato)
            {
                return true;
            }
            aux = aux->getSiguiente();
        } while (aux != this->cabeza);
    }
    return false;
}

// To ensure the templates are properly instantiated
template class ListaCircularDoble<int>;