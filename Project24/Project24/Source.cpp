#include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <cstdio>
#include <cstdlib>

using namespace std;

// Prototipos de las funciones nuevas
char* ingresarLetras(const char* msj);

// Función existente de ingresar números
char* ingresar(const char* msj) {
    char* dato = (char*)malloc(25 * sizeof(char));
    if (dato == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }
    char c;
    int i = 0;
    printf("%s: ", msj);
    while ((c = _getch()) != 13) {
        if ((c >= '0' && c <= '9') || c == 8) {
            if (c == 8 && i > 0) {
                printf("\b \b");
                i--;
            }
            else if (c != 8 && i < 25) {
                dato[i++] = c;
                printf("%c", c);
            }
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
    return dato;
}

template<typename T>
class Nodo {
public:
    T dato;
    Nodo* siguiente;
    Nodo* anterior;
};

template<typename T>
class EnlazarLista {
public:
    EnlazarLista();
    ~EnlazarLista();

    T getPrimero() const;
    T getUltimo() const;

    void insertarPrimero(T n);
    void insertarUltimo(T n);
    void eliminarPrimero();
    void eliminarUltimo();
    void mostrarFinalInicio() const;
    void mostrarInicioFinal() const;
    Nodo<T>* buscar(T n) const;

private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
};

template<typename T>
EnlazarLista<T>::EnlazarLista() {
    cabeza = new Nodo<T>;
    cola = new Nodo<T>;

    cabeza->siguiente = cola;
    cola->anterior = cabeza;
    cabeza->anterior = nullptr;
    cola->siguiente = nullptr;
}

template<typename T>
T EnlazarLista<T>::getPrimero() const {
    return cabeza->siguiente->dato;
}

template<typename T>
T EnlazarLista<T>::getUltimo() const {
    return cola->anterior->dato;
}

template<typename T>
void EnlazarLista<T>::insertarPrimero(T n) {
    Nodo<T>* nuevoNodo = new Nodo<T>();
    nuevoNodo->dato = n;
    nuevoNodo->anterior = cabeza;
    nuevoNodo->siguiente = cabeza->siguiente;

    cabeza->siguiente->anterior = nuevoNodo;
    cabeza->siguiente = nuevoNodo;
}

template<typename T>
void EnlazarLista<T>::insertarUltimo(T n) {
    Nodo<T>* nuevoNodo = new Nodo<T>();
    nuevoNodo->dato = n;
    nuevoNodo->anterior = cola->anterior;
    nuevoNodo->siguiente = cola;

    cola->anterior->siguiente = nuevoNodo;
    cola->anterior = nuevoNodo;
}

template<typename T>
void EnlazarLista<T>::eliminarPrimero() {
    if (cabeza->siguiente == cola) return;

    Nodo<T>* temp = cabeza->siguiente;
    cabeza->siguiente = temp->siguiente;
    temp->siguiente->anterior = cabeza;
    delete temp;
}

template<typename T>
void EnlazarLista<T>::eliminarUltimo() {
    if (cola->anterior == cabeza) return;

    Nodo<T>* temp = cola->anterior;
    cola->anterior = temp->anterior;
    temp->anterior->siguiente = cola;
    delete temp;
}

template<typename T>
void EnlazarLista<T>::mostrarFinalInicio() const {
    auto imprimir = [](const Nodo<T>* nodo) {
        std::cout << nodo->dato << " ";
        };
    Nodo<T>* actual = cola->anterior;
    while (actual != cabeza) {
        imprimir(actual);
        actual = actual->anterior;
    }
    std::cout << std::endl;
}

template<typename T>
void EnlazarLista<T>::mostrarInicioFinal() const {
    auto imprimir = [](const Nodo<T>* nodo) {
        std::cout << nodo->dato << " ";
        };
    Nodo<T>* actual = cabeza->siguiente;
    while (actual != cola) {
        imprimir(actual);
        actual = actual->siguiente;
    }
    std::cout << std::endl;
}

template<typename T>
Nodo<T>* EnlazarLista<T>::buscar(T n) const {
    Nodo<T>* actual = cabeza->siguiente;
    while (actual != cola) {
        if (actual->dato == n) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

template<typename T>
EnlazarLista<T>::~EnlazarLista() {
    while (cabeza->siguiente != cola) {
        eliminarPrimero();
    }
    delete cabeza;
    delete cola;
}

//----------------------------------
template<typename T>
using UnorderedMap = unordered_map<T, int>;

template<typename T>
string generarCorreo(const T& nombre1, const T& nombre2, const T& apellido, UnorderedMap<string>& conteoCorreo) {
    string baseCorreo = nombre1.substr(0, 1) + nombre2.substr(0, 1) + apellido;

    transform(baseCorreo.begin(), baseCorreo.end(), baseCorreo.begin(), ::tolower);

    string correo = baseCorreo;
    if (conteoCorreo[baseCorreo] > 0) {
        correo += to_string(conteoCorreo[baseCorreo]);
    }

    conteoCorreo[baseCorreo]++;

    correo += "@espe.edu.ec";

    return correo;
}

void cargarCorreosExistentes(const string& nombreArchivo, UnorderedMap<string>& conteoCorreo) {
    ifstream archivoEntrada(nombreArchivo);
    if (!archivoEntrada) {
        cerr << "No se pudo abrir el archivo existente. Se creará uno nuevo." << endl;
        return;
    }

    string linea;
    while (getline(archivoEntrada, linea)) {
        string baseCorreo = linea.substr(0, linea.find('@'));
        string parteNumerica = baseCorreo.substr(baseCorreo.length() - 1);

        if (isdigit(parteNumerica[0])) {
            string base = baseCorreo.substr(0, baseCorreo.length() - 1);
            int numero = stoi(parteNumerica);
            conteoCorreo[base] = max(conteoCorreo[base], numero + 1);
        }
        else {
            conteoCorreo[baseCorreo]++;
        }
    }

    archivoEntrada.close();
}

// Nueva función para ingresar solo letras
char* ingresarLetras(const char* msj) {
    char* dato = (char*)malloc(25 * sizeof(char));
    if (dato == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }
    char c;
    int i = 0;
    printf("%s: ", msj);
    while ((c = _getch()) != 13) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            dato[i++] = c;
            printf("%c", c);
        }
        else if (c == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
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
    return dato;
}

int main() {
    EnlazarLista<int> lista;
    int opcion, numero;
    char* input;
    do {
        cout << "Menu:\n";
        cout << "1. Insertar al inicio\n";
        cout << "2. Insertar al final\n";
        cout << "3. Mostrar de inicio a fin\n";
        cout << "4. Mostrar de fin a inicio\n";
        cout << "5. Buscar elemento\n";
        cout << "6. Ingresar solo letras\n";  // Nuevo menú para ingresar solo letras
        cout << "7. Salir\n";
        input = ingresar("Seleccione una opcion");
        cout << endl;
        opcion = atoi(input);
        free(input);

        switch (opcion) {
        case 1:
            input = ingresar("Ingrese un numero");
            numero = atoi(input);
            free(input);
            lista.insertarPrimero(numero);
            system("pause");
            break;
        case 2:
            input = ingresar("Ingrese un numero");
            numero = atoi(input);
            free(input);
            lista.insertarPrimero(numero);
            system("pause");
            break;
        case 3:
            lista.mostrarInicioFinal();
            system("pause");
            break;
        case 4:
            lista.mostrarFinalInicio();
            system("pause");
            break;
        case 5:
            input = ingresar("Ingrese el numero que desea buscar: ");
            numero = atoi(input);
            free(input);
            if (lista.buscar(numero)) {
                cout << "Elemento encontrado." << endl;
            }
            else {
                cout << "Elemento no encontrado." << endl;
            }
            system("pause");
            break;
        case 6:
            input = ingresarLetras("Ingrese solo letras");
            printf("\nTexto ingresado: %s\n", input);
            free(input);
            system("pause");
            break;
        case 7:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
            break;
        }
        system("cls");
    } while (opcion != 7);

    return 0;
}