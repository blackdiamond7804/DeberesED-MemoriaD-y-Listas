#pragma once
#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include "NodoDoble.h"
#include <functional>
#include <iostream>

using namespace std;

template<typename T>
class ListaCircularDoble {
private:
    NodoDoble<T>* cabeza;
    NodoDoble<T>* cola;
public:
    ListaCircularDoble();
    ~ListaCircularDoble();
    void insertar(T);
    void eliminar(T);
    void mostrar(function<void(T)>);
    bool buscar(T);
    T encontrarMaximo();  // Nueva función
};

#endif