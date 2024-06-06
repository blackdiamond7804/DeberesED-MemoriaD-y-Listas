#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

// Mapa para llevar el registro de cuántos correos se han generado con el mismo nombre base
std::unordered_map<std::string, int> emailCount;

// Función para generar correos electrónicos
std::string generateEmail(const std::string& firstName1, const std::string& firstName2, const std::string& lastName) {
    // Obtener las dos primeras letras de los nombres y el apellido completo
    std::string emailBase = firstName1.substr(0, 1) + firstName2.substr(0, 1) + lastName;

    // Convertir a minúsculas para estandarizar el correo
    for (auto& c : emailBase) {
        c = tolower(c);
    }

    // Verificar si el correo base ya existe y generar un nuevo correo con un número secuencial si es necesario
    std::string email = emailBase;
    if (emailCount[emailBase] > 0) {
        email += std::to_string(emailCount[emailBase]);
    }

    // Incrementar el contador de este correo base en el mapa
    emailCount[emailBase]++;

    // Añadir el dominio al correo
    email += "@espe.edu.ec";

    return email;
}

int main() {
    std::string firstName1, firstName2, lastName;
    char continueInput;
    std::ofstream outFile("correos_generados.txt", std::ios::app); // Abre el archivo en modo adjuntar

    if (!outFile) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return 1;
    }

    do {
        // Permitir al usuario ingresar los nombres y apellidos
        std::cout << "Ingrese el primer nombre: ";
        std::cin >> firstName1;
        std::cout << "Ingrese el segundo nombre: ";
        std::cin >> firstName2;
        std::cout << "Ingrese el apellido: ";
        std::cin >> lastName;

        // Generar el correo electrónico
        std::string email = generateEmail(firstName1, firstName2, lastName);

        // Mostrar el correo generado
        std::cout << "Correo generado: " << email << std::endl;

        // Escribir el correo generado en el archivo
        outFile << email << std::endl;

        // Preguntar al usuario si desea continuar ingresando más nombres y apellidos
        std::cout << "¿Desea ingresar otro nombre? (s/n): ";
        std::cin >> continueInput;

    } while (continueInput == 's' || continueInput == 'S');

    outFile.close(); // Cerrar el archivo

    return 0;
}
