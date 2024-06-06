#pragma once
#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
private:
    T dato;
    Nodo* siguiente;
    Nodo* anterior;
public:
    Nodo(T);
    void setDato(T);
    void setSiguiente(Nodo*);
    void setAnterior(Nodo*);
    T getDato();
    Nodo* getSiguiente();
    Nodo* getAnterior();
};

#endif // NODO_H
