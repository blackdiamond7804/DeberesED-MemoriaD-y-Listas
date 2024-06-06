#include "ListasCirculares.cpp"
#include <iostream>
#include <string>
#include <functional>
using namespace std;

bool esEntero(const string&);

int main() {
    ListaCircular<int>* lista = new ListaCircular<int>();
    int opcion, dato;
    string linea;

    auto obtenerEntrada = [](const string& mensaje, function<bool(const string&)> validar) -> int {
        string entrada;
        do {
            cout << mensaje;
            getline(cin, entrada);
        } while (!validar(entrada));
        return stoi(entrada);
        };

    do {
        system("cls");
        cout << "*********** Listas Circulares ***********" << endl;
        cout << "1. Insertar" << endl;
        cout << "2. Buscar" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Mostrar" << endl;
        cout << "5. Obtener tamaño de la lista" << endl;
        cout << "6. Mostrar números pares" << endl; // Nueva opción
        cout << "7. Salir" << endl;

        opcion = obtenerEntrada("Opción: ", esEntero);

        switch (opcion) {
        case 1:
            dato = obtenerEntrada("Ingrese el dato a insertar: ", esEntero);
            lista->Insertar(dato);
            break;
        case 2:
            dato = obtenerEntrada("Ingrese el dato a buscar: ", esEntero);
            lista->Buscar(dato);
            break;
        case 3:
            dato = obtenerEntrada("Ingrese el dato a eliminar: ", esEntero);
            lista->Eliminar(dato);
            break;
        case 4:
            lista->Mostrar();
            break;
        case 5:
            cout << "Tamaño de la lista: " << lista->Tamano() << endl;
            break;
        case 6: {
            ListaCircular<int>* listaPares = lista->FiltrarPares();
            cout << "Números pares en la lista: " << endl;
            listaPares->Mostrar();
            delete listaPares;
            break;
        }
        case 7:
            break;
        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
        }
        if (opcion != 7) {
            system("pause");
        }
    } while (opcion != 7);

    delete lista;
    return 0;
}

//Funcion para validar
bool esEntero(const string& linea) {
    if (linea.empty() || (linea.size() == 1 && !isdigit(linea[0]))) {
        return false;
    }
    size_t inicio = (linea[0] == '+' || linea[0] == '-') ? 1 : 0;
    for (size_t i = inicio; i < linea.size(); ++i) {
        if (!isdigit(linea[i])) {
            return false;
        }
    }
    return true;
}