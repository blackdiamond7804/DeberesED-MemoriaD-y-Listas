#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

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

// Función para leer los correos ya existentes y actualizar el mapa emailCount
void loadExistingEmails(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "No se pudo abrir el archivo existente. Se creará uno nuevo." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        // Parsear el correo y actualizar el mapa emailCount
        std::string emailBase = line.substr(0, line.find('@'));
        std::string numberPart = emailBase.substr(emailBase.length() - 1);

        // Si el último carácter es un número, procesarlo
        if (isdigit(numberPart[0])) {
            std::string base = emailBase.substr(0, emailBase.length() - 1);
            int number = std::stoi(numberPart);
            emailCount[base] = std::max(emailCount[base], number + 1);
        }
        else {
            emailCount[emailBase]++;
        }
    }

    inFile.close();
}

int main() {
    std::string firstName1, firstName2, lastName;
    char continueInput;
    std::string filename = "correos_generados.txt";

    // Cargar correos existentes del archivo
    loadExistingEmails(filename);

    std::ofstream outFile(filename, std::ios::app); // Abre el archivo en modo adjuntar
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
