#pragma once
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
    ListaCircular<T>* FiltrarPares(); // Nueva función
};