#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <conio.h>
#include <cstdio>
#include <cstdlib>

using namespace std;

template<typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

// Lista doblemente enlazada
template<typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertFront(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    Node<T>* getHead() const {
        return head;
    }
};

template<typename T>
using UnorderedMap = std::unordered_map<T, int>;

string ingresarLetras(const string& msj) {
    string dato;
    cout << msj << ": ";
    char c;
    while ((c = _getch()) != 13) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            dato.push_back(c);
            cout << c;
        }
        else if (c == 8) {
            if (!dato.empty()) {
                dato.pop_back();
                cout << "\b \b";
            }
        }
    }
    cout << endl;
    return dato;
}

string generarCorreo(const string& nombre1, const string& nombre2, const string& apellido, UnorderedMap<string>& conteoCorreo) {
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
        size_t pos = linea.find('@');
        if (pos == string::npos) continue;
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
    while ((c = _getch()) != 13) {
        if (c >= '0' && c <= '9') {
            dato[i++] = c;
            printf("%c", c);
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

int main() {
    string nombre1, nombre2, apellido;
    char continuar = 's';
    string nombreArchivo = "correos_generados.txt";
    UnorderedMap<string> conteoCorreo;
    int opcion;
    char* input;

    cargarCorreosExistentes(nombreArchivo, conteoCorreo);

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
            nombre1 = ingresarLetras("Ingrese el primer nombre");
            nombre2 = ingresarLetras("Ingrese el segundo nombre");
            apellido = ingresarLetras("Ingrese el apellido");

            {
                string correo = generarCorreo(nombre1, nombre2, apellido, conteoCorreo);
                cout << "Correo generado: " << correo << endl;

                archivoSalida << "Usuario: " << nombre1 << " " << nombre2 << " " << apellido << endl;
                archivoSalida << "Correo: " << correo << endl << endl;

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