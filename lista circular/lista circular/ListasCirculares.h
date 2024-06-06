#ifndef LISTASCIRCULARES_H
#define LISTASCIRCULARES_H

#include "Nodo.h"

template<typename T>
class ListaCircular {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    int tamano;
public:
    ListaCircular();
    ~ListaCircular();
    void Insertar(T);
    void Buscar(T);
    void Eliminar(T);
    void Mostrar();
    int Tamano();
};

#endif // LISTASCIRCULARES_H