#pragma once
#include<iostream>


template <typename T>
class NodoDoble
{
private:
    T dato;
    NodoDoble* siguiente;
    NodoDoble* anterior;
public:
    NodoDoble(T);
    ~NodoDoble();
    void setDato(T);
    T getDato();
    void setSiguiente(NodoDoble*);
    NodoDoble* getSiguiente();
    void setAnterior(NodoDoble*);
    NodoDoble* getAnterior();
};