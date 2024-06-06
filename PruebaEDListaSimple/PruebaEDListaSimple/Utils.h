#pragma once
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

template<typename T>
using UnorderedMap = std::unordered_map<T, int>;

string ingresarLetras(const string& msj);
string generarCorreo(const string& nombre1, const string& nombre2, const string& apellido, UnorderedMap<string>& conteoCorreo);
void cargarCorreosExistentes(const string& nombreArchivo, UnorderedMap<string>& conteoCorreo, set<string>& cedulas);
char* ingresar(const char* msj);
bool validarCedulaEcuatoriana(const string& cedula);