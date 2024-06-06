#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include <cstdlib>
#include "Doubly_linked_listr.h"
#include "utils.h"

using namespace std;

int main() {
    string nombre1, nombre2, apellido, cedula;
    char continuar = 's';
    string nombreArchivo = "correos_generados.txt";
    UnorderedMap<string> conteoCorreo;
    set<string> cedulas;
    int opcion;
    char* input;

    cargarCorreosExistentes(nombreArchivo, conteoCorreo, cedulas);

    ofstream archivoSalida(nombreArchivo, ios::app);
    if (!archivoSalida) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return 1;
    }

    do {
        cout << "\tMenu\n";
        cout << "1. Ingresar una persona" << endl;
        cout << "2. Salir" << endl;

        input = ingresar("Ingrese una opcion: ");
        opcion = atoi(input);
        free(input);

        switch (opcion) {
        case 1:
            cedula = ingresar("Ingrese la cedula");

            if (!validarCedulaEcuatoriana(cedula)) {
                cout << "Cédula no válida." << endl;
                break;
            }

            if (cedulas.find(cedula) != cedulas.end()) {
                cout << "La cédula ya existe." << endl;
                break;
            }

            nombre1 = ingresarLetras("Ingrese el primer nombre");
            nombre2 = ingresarLetras("Ingrese el segundo nombre");
            apellido = ingresarLetras("Ingrese el apellido");

            {
                string correo = generarCorreo(nombre1, nombre2, apellido, conteoCorreo);
                cout << "Correo generado: " << correo << endl;

                archivoSalida << "Usuario: " << nombre1 << " " << nombre2 << " " << apellido << endl;
                archivoSalida << "Cedula: " << cedula << endl;
                archivoSalida << "Correo: " << correo << endl << endl;

                cedulas.insert(cedula);
            }
            system("pause");
            break;
        case 2:
            cout << "Saliendo del programa...." << endl;
            continuar = 'n';
            break;
        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
        }

        cout << endl;
        if (continuar == 's' || continuar == 'S') {
            system("cls");
        }
    } while (continuar == 's' || continuar == 'S');

    archivoSalida.close();

    system("pause");
    return 0;
}
