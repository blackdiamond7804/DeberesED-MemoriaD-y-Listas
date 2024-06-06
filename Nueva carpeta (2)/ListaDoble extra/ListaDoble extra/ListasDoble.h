#pragma once
#include<iostream>
#include"Nodo.h"

template<typename T>
class ListaDoble {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;

public:
    ListaDoble();
    ~ListaDoble();
    void Insertar(T);
    void Buscar(T);
    void Eliminar(T);
    void Mostrar();
    void Revertir();
};