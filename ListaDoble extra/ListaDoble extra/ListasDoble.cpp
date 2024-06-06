#include "ListasDoble.h"

using namespace std;

template <typename T>
ListaDoble<T>::ListaDoble() {
    primero = nullptr;
    ultimo = nullptr;
}

template <typename T>
ListaDoble<T>::~ListaDoble() {
    if (primero != nullptr) {
        Nodo<T>* aux = primero;
        do {
            Nodo<T>* temp = aux;
            aux = aux->getSiguiente();
            delete temp;
        } while (aux != primero);
    }
}

template <typename T>
void ListaDoble<T>::Insertar(T _dato) {
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (primero == nullptr) {
        primero = nuevo;
        ultimo = nuevo;
        primero->setSiguiente(primero);
        primero->setAnterior(ultimo);
    }
    else {
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        nuevo->setSiguiente(primero);
        primero->setAnterior(nuevo);
        ultimo = nuevo;
    }
}

template <typename T>
void ListaDoble<T>::Buscar(T _dato) {
    auto encontrarDato = [=]() {
        Nodo<T>* aux = primero;
        do {
            if (aux->getDato() == _dato) {
                cout << "El dato " << _dato << " se encuentra en la lista" << endl;
                return true;
            }
            aux = aux->getSiguiente();
        } while (aux != primero);
        return false;
        };

    if (!encontrarDato()) {
        cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
    }
}

template <typename T>
void ListaDoble<T>::Eliminar(T _dato) {
    auto eliminarDato = [=]() -> bool {
        Nodo<T>* aux = primero;
        do {
            if (aux->getDato() == _dato) {
                if (aux == primero && aux == ultimo) {
                    primero = nullptr;
                    ultimo = nullptr;
                }
                else if (aux == primero) {
                    primero = primero->getSiguiente();
                    primero->setAnterior(ultimo);
                    ultimo->setSiguiente(primero);
                }
                else if (aux == ultimo) {
                    ultimo = ultimo->getAnterior();
                    ultimo->setSiguiente(primero);
                    primero->setAnterior(ultimo);
                }
                else {
                    aux->getAnterior()->setSiguiente(aux->getSiguiente());
                    aux->getSiguiente()->setAnterior(aux->getAnterior());
                }
                delete aux;
                return true;
            }
            aux = aux->getSiguiente();
        } while (aux != primero);
        return false;
        };

    if (eliminarDato()) {
        cout << "El dato " << _dato << " se ha eliminado de la lista" << endl;
    }
    else {
        cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
    }
}

template <typename T>
void ListaDoble<T>::Mostrar() {
    auto mostrarLista = [&]() {
        if (primero == nullptr) {
            cout << "La lista está vacía" << endl;
            return;
        }

        Nodo<T>* aux = primero;
        do {
            cout << aux->getDato() << " -> ";
            aux = aux->getSiguiente();
        } while (aux != primero);
        cout << endl;
        };
    mostrarLista();
}

template <typename T>
void ListaDoble<T>::Revertir() {
    if (primero == nullptr) {
        cout << "La lista está vacía" << endl;
        return;
    }

    Nodo<T>* actual = primero;
    Nodo<T>* temp = nullptr;

    do {
        temp = actual->getAnterior();
        actual->setAnterior(actual->getSiguiente());
        actual->setSiguiente(temp);
        actual = actual->getAnterior();
    } while (actual != primero);

    temp = primero;
    primero = ultimo;
    ultimo = temp;

    cout << "La lista se ha revertido" << endl;
}

// Explicit template instantiation
template class ListaDoble<int>;
template class ListaDoble<float>;
template class ListaDoble<double>;
template class ListaDoble<string>;