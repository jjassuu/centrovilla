#include "person.h"
#include <regex>
#include <iostream>
#include "main.h"
// Validar el formato del DNI
bool Person::validarDNI(const std::string& dni) {
    std::regex formatoDNI("^\\d{8}[A-Za-z]$");
    if (!std::regex_match(dni, formatoDNI)) {
        std::cerr << "Error: El DNI debe tener 8 números seguidos de una letra.\n";
        return false;
    }
    return true;
}

// Validar la edad
bool Person::validarEdad(int edad) {
    if (edad <= 0) {
        std::cerr << "Error: La edad debe ser un número positivo.\n";
        return false;
    }
    return true;
}

// Validar el formato del correo electrónico
bool Person::validarEmail(const std::string& email) {
    std::regex patronEmail(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!std::regex_match(email, patronEmail)) {
        std::cerr << "Error: El email no tiene un formato válido.\n";
        return false;
    }
    return true;
}

// Validar el formato del número de teléfono (9 dígitos)
bool Person::validarTelefono(const std::string& telefono) {
    std::regex patronTelefono("^\\d{9}$");
    if (!std::regex_match(telefono, patronTelefono)) {
        std::cerr << "Error: El teléfono debe contener exactamente 9 dígitos.\n";
        return false;
    }
    return true;
}

// Solicitar datos de la persona desde la consola
void Person::getPersonData() {
    do {
        std::cout << "Introduce el DNI (8 números seguidos de una letra): ";
        std::getline(std::cin, dni);
        if (!validarDNI(dni)) {
            std::cerr << "Por favor, introduce un DNI válido.\n";
        }
    } while (!validarDNI(dni));
    do {
        std::cout << "Introduce el nombre: ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            std::cerr << "Error: El nombre no puede estar vacío. Por favor, introduce un nombre válido.\n";
        }
    } while (nombre.empty());

    do {
        std::cout << "Introduce la edad: ";
        if (!obtenerEntrada(edad) || !validarEdad(edad)) {
            std::cerr << "Por favor, introduce una edad válida (mayor que 0).\n";
        }
        else {
            break;
        }
    } while (!validarEdad(edad));

    do {
        std::cout << "Introduce el número de teléfono (9 dígitos): ";
        std::getline(std::cin, telefono);
        if (!validarTelefono(telefono)) {
            std::cerr << "Por favor, introduce un número de teléfono válido.\n";
        }
    } while (!validarTelefono(telefono));

    std::cout << "Introduce la dirección: ";
    std::getline(std::cin, direccion);

    do {
        std::cout << "Introduce el email (formato válido): ";
        std::getline(std::cin, email);
        if (!validarEmail(email)) {
            std::cerr << "Por favor, introduce un email válido.\n";
        }
    } while (!validarEmail(email));
}

// Mostrar los datos de la persona
void Person::showPersonData() const {
    std::cout << "DNI: " << dni << ", Nombre: " << nombre
        << ", Edad: " << edad << ", Teléfono: " << telefono
        << ", Dirección: " << direccion << ", Email: " << email << std::endl;
}
