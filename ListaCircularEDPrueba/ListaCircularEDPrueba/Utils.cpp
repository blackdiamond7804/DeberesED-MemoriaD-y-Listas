// Utils.cpp
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <conio.h>
#include <cstdio>
#include <cstdlib>

using namespace std;

string ingresarLetras(const string& msj) {
    string dato;
    cout << msj << ": ";
    char c;
    while ((c = _getch()) != 13) { // Enter key
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            dato.push_back(c);
            cout << c;
        }
        else if (c == 8 && !dato.empty()) { // Backspace key
            dato.pop_back();
            cout << "\b \b";
        }
    }
    cout << endl;
    return dato;
}

string generarCorreo(const string& nombre1, const string& nombre2, const string& apellido, UnorderedMap<string>& conteoCorreo) {
    auto toLower = [](const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
        };

    string baseCorreo = toLower(nombre1.substr(0, 1) + nombre2.substr(0, 1) + apellido);
    string correo = baseCorreo;
    if (conteoCorreo[baseCorreo] > 0) {
        correo += to_string(conteoCorreo[baseCorreo]);
    }
    conteoCorreo[baseCorreo]++;
    correo += "@espe.edu.ec";
    return correo;
}

void cargarCorreosExistentes(const string& nombreArchivo, UnorderedMap<string>& conteoCorreo, set<string>& cedulas) {
    ifstream archivoEntrada(nombreArchivo);
    if (!archivoEntrada) {
        cerr << "No se pudo abrir el archivo existente. Se creará uno nuevo." << endl;
        return;
    }
    string linea;
    while (getline(archivoEntrada, linea)) {
        size_t pos = linea.find('@');
        if (pos != string::npos) {
            string baseCorreo = linea.substr(0, pos);
            if (!baseCorreo.empty()) {
                char lastChar = baseCorreo.back();
                if (isdigit(lastChar)) {
                    string base = baseCorreo.substr(0, baseCorreo.length() - 1);
                    int numero = lastChar - '0';
                    conteoCorreo[base] = max(conteoCorreo[base], numero + 1);
                }
                else {
                    conteoCorreo[baseCorreo]++;
                }
            }
        }
        else {
            size_t posCedula = linea.find("Cedula: ");
            if (posCedula != string::npos) {
                string cedula = linea.substr(posCedula + 8);
                cedulas.insert(cedula);
            }
        }
    }
    archivoEntrada.close();
}

char* ingresar(const char* msj) {
    char* dato = (char*)malloc(25 * sizeof(char));
    if (dato == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }
    char c;
    int i = 0;
    printf("%s: ", msj);
    while ((c = _getch()) != 13) { // Enter key
        if (c >= '0' && c <= '9') {
            dato[i++] = c;
            printf("%c", c);
        }
        else if (c == 8 && i > 0) { // Backspace key
            i--;
            printf("\b \b");
        }
        if (i >= 25) {
            dato = (char*)realloc(dato, (i + 1) * sizeof(char));
            if (dato == NULL) {
                printf("Error al asignar memoria\n");
                exit(1);
            }
        }
    }
    dato[i] = '\0';
    printf("\n");
    return dato;
}

bool validarCedulaEcuatoriana(const string& cedula) {
    if (cedula.length() != 10) {
        return false;
    }

    for (char c : cedula) {
        if (!isdigit(c)) {
            return false;
        }
    }

    int digitos[10];
    for (int i = 0; i < 10; i++) {
        digitos[i] = cedula[i] - '0';
    }

    int provincia = digitos[0] * 10 + digitos[1];
    if (provincia < 1 || provincia > 24) {
        return false;
    }

    if (digitos[2] < 0 || digitos[2] > 6) {
        return false;
    }

    int suma = 0;
    for (int i = 0; i < 9; i++) {
        if (i % 2 == 0) {
            int producto = digitos[i] * 2;
            if (producto > 9) {
                producto -= 9;
            }
            suma += producto;
        }
        else {
            suma += digitos[i];
        }
    }

    int digitoVerificadorCalculado = (10 - (suma % 10)) % 10;
    return digitoVerificadorCalculado == digitos[9];
}