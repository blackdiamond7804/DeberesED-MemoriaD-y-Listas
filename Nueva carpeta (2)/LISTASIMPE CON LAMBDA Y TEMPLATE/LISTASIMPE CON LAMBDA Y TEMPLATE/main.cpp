#include"ListasSimples.cpp"
#include<stdlib.h>

using namespace std;

bool esEntero(string);

int main() {
	ListaSimples<int>* lista = new ListaSimples<int>();
	int opcion, dato;
	string linea, i, b, e;
	bool rep = true;
	bool repite = true;

	do {
		system("cls");
		cout << "***********Listas Simples************" << endl;
		cout << "1. Insertar" << endl;
		cout << "2. Buscar" << endl;
		cout << "3. Eliminar" << endl;
		cout << "4. Mostrar" << endl;
		cout << "5. Salir" << endl;
		cout << "Opcion: ";
		do {
			getline(cin, linea);

			if (esEntero(linea)) {
				repite = false;
				opcion = atoi(linea.c_str());
				if (opcion > 5 || opcion < 1) {
					repite = true;
				}
			}
			else {
				cout << "No has ingresado un valor entero. Intentalo nuevamente" << endl;
			}
		} while (repite);
		opcion = atoi(linea.c_str());
		switch (opcion) {
		case 1:
			rep = true;
			do {
				cout << "Ingrese el dato a insertar: ";
				getline(cin, i);

				if (esEntero(i)) {
					rep = false;
					dato = atoi(i.c_str());
				}
				else {
					cout << "No has ingresado un valor entero. Intentalo nuevamente" << endl;
				}
			} while (rep);
			lista->Insertar(dato);
			break;
		case 2:
			rep = true;
			do {
				cout << "Ingrese el dato a buscar: ";
				getline(cin, b);

				if (esEntero(b)) {
					rep = false;
					dato = atoi(b.c_str());
				}
				else {
					cout << "No has ingresado un valor entero. Intentalo nuevamente" << endl;
				}
			} while (rep);
			lista->Buscar(dato);
			break;
		case 3:
			rep = true;
			do {
				cout << "Ingrese el dato a eliminar: ";
				getline(cin, e);

				if (esEntero(e)) {
					rep = false;
					dato = atoi(e.c_str());
				}
				else {
					cout << "No has ingresado un valor entero. Intentalo nuevamente" << endl;
				}
			} while (rep);
			lista->Eliminar(dato);
			break;
		case 4:
			lista->Mostrar();
			break;
		}
		system("pause");
	} while (opcion != 5);
	return 0;
}

//Funcion para validar si un string es un entero
bool esEntero(string linea) {
	bool esEntero = true;
	int longitud = linea.size();

	if (longitud == 0) {
		esEntero = false;
	}
	else if (longitud == 1 && !isdigit(linea[0])) {
		esEntero = false;
	}
	else {
		int indice = 0;
		if (linea[0] == '+' || linea[0] == '-') {
			indice = 1;
		}
		else {
			indice = 0;
		}

		while (indice < longitud) {
			if (!isdigit(linea[indice])) {
				esEntero = false;
				break;
			}
			indice++;
		}
	}
	return esEntero;
}