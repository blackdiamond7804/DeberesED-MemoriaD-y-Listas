#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>

// Mapa para llevar el registro de cuántos correos se han generado con el mismo nombre base
std::unordered_map<std::string, int> emailCount;

// Vector para llevar el registro de los nombres y correos ya existentes
std::vector<std::string> existingEntries;

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
        // Parsear la línea en nombres y correo
        std::istringstream iss(line);
        std::string namePart, emailPart;
        std::getline(iss, namePart, ':');
        std::getline(iss, emailPart);

        // Añadir la entrada al vector de entradas existentes
        existingEntries.push_back(line);

        // Actualizar el mapa emailCount
        std::string emailBase = emailPart.substr(0, emailPart.find('@'));
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

// Función para verificar si los nombres ya existen en las entradas existentes
bool nameExists(const std::string& firstName1, const std::string& firstName2, const std::string& lastName) {
    std::string fullName = firstName1 + " " + firstName2 + " " + lastName;
    for (const std::string& entry : existingEntries) {
        if (entry.find(fullName) != std::string::npos) {
            return true;
        }
    }
    return false;
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

        // Verificar si los nombres ya existen
        if (nameExists(firstName1, firstName2, lastName)) {
            // Si el nombre existe, agregar solo el correo al archivo
            outFile << " " << email << std::endl;
        }
        else {
            // Si el nombre no existe, agregar el nombre y el correo al archivo
            outFile << firstName1 << " " << firstName2 << " " << lastName << ": " << email << std::endl;
            // Añadir la nueva entrada al vector de entradas existentes
            existingEntries.push_back(firstName1 + " " + firstName2 + " " + lastName + ": " + email);
        }

        // Preguntar al usuario si desea continuar ingresando más nombres y apellidos
        std::cout << "¿Desea ingresar otro nombre? (s/n): ";
        std::cin >> continueInput;

    } while (continueInput == 's' || continueInput == 'S');

    outFile.close(); // Cerrar el archivo

    return 0;
}