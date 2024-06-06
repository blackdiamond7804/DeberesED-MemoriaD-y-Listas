#pragma once
#ifndef NODO_H
#define NODO_H

template<typename T>
class Nodo {
private:
    T dato;
    Nodo* siguiente;
public:
    Nodo(T);
    void setDato(T);
    T getDato();
    void setSiguiente(Nodo*);
    Nodo* getSiguiente();
};

#endif // NODO_H