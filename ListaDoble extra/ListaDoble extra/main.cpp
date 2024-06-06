#include "ListasDoble.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool esEntero(string);

int main() {
    ListaDoble<int>* lista = new ListaDoble<int>();
    int opcion, dato;
    string linea;
    bool rep = true;

    //validacion usando lambda
    auto obtenerDato = [](string& entrada) -> int {
        bool valido;
        do {
            cout << entrada;
            getline(cin, entrada);
            if (esEntero(entrada)) {
                valido = true;
            }
            else {
                cout << "No has ingresado un valor entero. Inténtalo nuevamente." << endl;
                valido = false;
            }
        } while (!valido);
        return stoi(entrada);
        };

    do {
        system("cls");
        cout << "*********** Listas Circulares Dobles ***********" << endl;
        cout << "1. Insertar" << endl;
        cout << "2. Buscar" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Mostrar" << endl;
        cout << "5. Revertir" << endl;  // Agregar opción para revertir
        cout << "6. Salir" << endl;
        cout << "Opción: ";
        getline(cin, linea);

        auto obtenerOpcion = [&](string& entrada) -> int {
            if (esEntero(entrada)) {
                return stoi(entrada);
            }
            else {
                cout << "No has ingresado un valor entero. Inténtalo nuevamente." << endl;
                return -1;
            }
            };

        opcion = obtenerOpcion(linea);

        switch (opcion) {
        case 1:
            dato = obtenerDato(linea = "Ingrese el dato a insertar: ");
            lista->Insertar(dato);
            break;
        case 2:
            dato = obtenerDato(linea = "Ingrese el dato a buscar: ");
            lista->Buscar(dato);
            break;
        case 3:
            dato = obtenerDato(linea = "Ingrese el dato a eliminar: ");
            lista->Eliminar(dato);
            break;
        case 4:
            lista->Mostrar();
            break;
        case 5:
            lista->Revertir();  // Llamar a la función Revertir
            break;
        case 6:
            delete lista;
            return 0;
        default:
            cout << "Opción no válida. Inténtalo nuevamente." << endl;
        }
        system("pause");
    } while (opcion != 6);

    return 0;
}

bool esEntero(string linea) {
    if (linea.empty()) return false;
    if (linea[0] == '-' || linea[0] == '+') linea = linea.substr(1);
    return !linea.empty() && all_of(linea.begin(), linea.end(), ::isdigit);
}