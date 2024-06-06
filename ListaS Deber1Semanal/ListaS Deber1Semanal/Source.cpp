#include<iostream>
#include<stdlib.h>

using namespace std;

struct Nodo {
	int dato;
	Nodo* siguiente;
} *primero, * ultimo;

void insertar();
void imprimir();
void buscar(int datos);

int main() {

	insertar();
	insertar();
	insertar();
	insertar();
	imprimir();
	buscar(30);

	return 0;
}

void insertar() {
	Nodo* nuevo = new Nodo();
	cout << "Ingerse el nuevo dato: ";
	cin >> nuevo->dato;

	if (primero == nullptr){
		primero = nuevo;
		primero->siguiente = nullptr;
		ultimo = nuevo;
	}
	else {
		ultimo->siguiente = nuevo;
		nuevo->siguiente = nullptr;
		ultimo = nuevo;
	}
	cout << "Registro guardado!" << endl;
}

void imprimir() {

	cout << "Imprimiendo la lista: " << endl;
	Nodo* actual = new Nodo();
	actual = primero;

	if (primero != nullptr) {

		while (actual != nullptr) {
			cout << " " << actual->dato;
			actual = actual->siguiente;
		}
		cout << "\n";
	}
	else {
		cout << "Lista Vacia";
	}
}

void buscar(int dat) {

	int cont = 0;
	int pos = 0;
	bool flag;

	cout << "Buscando: " << dat <<"...."<< endl;
	Nodo* actual = new Nodo();
	actual = primero;
	if (primero != nullptr) {
		while (actual != nullptr) {
			cont++;
			if (actual->dato==dat) {
				actual = actual->siguiente;
				flag = true;
				pos = cont;
			}
			else {
				actual = actual->siguiente;
				flag = false;
			}
		}
		if (flag) {
			cout << "Encontrado en la posicion: " << pos << endl;
		}
		else {
			cout << "No encontrado......" <<endl;
		}
	}
	else {
		cout << "Lista Vacia";
	}
}