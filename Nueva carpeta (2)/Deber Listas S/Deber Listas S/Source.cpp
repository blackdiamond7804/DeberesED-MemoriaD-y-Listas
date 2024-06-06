#include<iostream>
#include<functional>
#include<string.h>

using namespace std;

//Insercion de lista Simple al inicio

template<typename T>
class ListaSimple;

template<typename T>
class Nodo {

	T dato;
	Nodo* siguiente;
	friend class ListaSimple<T>;
public:
	Nodo(T n) {

		dato = n;
		siguiente = nullptr;
	}
	~Nodo(){}
};

template<typename T>
class ListaSimple {

	Nodo<T>* incio;
	unsigned int tam;

public:

	ListaSimple(){
	
		inicio = nullptr;
		tam = 0;

	}
	~ListaSimple(){}

	void InsertarInicio(T dato) {

		Nodo<T>* nuevoNodo = new Nodo<T>(dato);

		//Saber si es que la lista esta vacio o saber si tiene nodos existentes
		if (inicio == nullptr) {
			inicio = nuevoNodo;
		}
		else {
			nuevoNodo->siguiente = incio;
			inicio = nuevoNodo;

		}

		//Incrementar tamanio de la lista al implementar el nuevo nodo
		tam++;
	}
};



int main() {

	ListaSimple<int> numeros;
	ListaSimple<string>cadenas;

}