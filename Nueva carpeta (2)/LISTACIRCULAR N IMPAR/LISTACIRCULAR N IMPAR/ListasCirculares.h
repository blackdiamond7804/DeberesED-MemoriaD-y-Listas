#ifndef LISTASCIRCULARES_H
#define LISTASCIRCULARES_H

#include "Nodo.h"
#include <functional>

template<typename T>
class ListaCircular {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    int tamano;
    void FiltrarRecursivo(Nodo<T>*, ListaCircular<T>*, std::function<bool(T)>);

public:
    ListaCircular();
    ~ListaCircular();
    void Insertar(T);
    void Buscar(T);
    void Eliminar(T);
    void Mostrar();
    int Tamano();
    ListaCircular<T>* FiltrarPares();
    ListaCircular<T>* FiltrarImpares(); // Nueva función
};

#endif // LISTASCIRCULARES_H

