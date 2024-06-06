#pragma once
#include<iostream>
#include<string>

using namespace std;

template<typename T>
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