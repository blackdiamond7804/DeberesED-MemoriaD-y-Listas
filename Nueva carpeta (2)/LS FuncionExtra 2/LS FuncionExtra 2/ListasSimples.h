#pragma once
#include "Nodo.h"

using namespace std;

template<typename T>
class ListaSimples {
private:
    Nodo<T>* cabeza;
public:
    ListaSimples();
    void Insertar(T);
    void Buscar(T);
    void Eliminar(T);
    void Mostrar();
    int Contar(); // Nueva funci�n para contar elementos
};