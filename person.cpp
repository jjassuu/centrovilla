#include "person.h"
#include <regex>
#include <iostream>
#include "main.h"
// Validar el formato del DNI
bool Person::validarDNI(const std::string& dni) {
    std::regex formatoDNI("^\\d{8}[A-Za-z]$");
    if (!std::regex_match(dni, formatoDNI)) {
        std::cerr << "Error: El DNI debe tener 8 n�meros seguidos de una letra.\n";
        return false;
    }
    return true;
}

// Validar la edad
bool Person::validarEdad(int edad) {
    if (edad <= 0) {
        std::cerr << "Error: La edad debe ser un n�mero positivo.\n";
        return false;
    }
    return true;
}

// Validar el formato del correo electr�nico
bool Person::validarEmail(const std::string& email) {
    std::regex patronEmail(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!std::regex_match(email, patronEmail)) {
        std::cerr << "Error: El email no tiene un formato v�lido.\n";
        return false;
    }
    return true;
}

// Validar el formato del n�mero de tel�fono (9 d�gitos)
bool Person::validarTelefono(const std::string& telefono) {
    std::regex patronTelefono("^\\d{9}$");
    if (!std::regex_match(telefono, patronTelefono)) {
        std::cerr << "Error: El tel�fono debe contener exactamente 9 d�gitos.\n";
        return false;
    }
    return true;
}

// Solicitar datos de la persona desde la consola
void Person::getPersonData() {
    do {
        std::cout << "Introduce el DNI (8 n�meros seguidos de una letra): ";
        std::getline(std::cin, dni);
        if (!validarDNI(dni)) {
            std::cerr << "Por favor, introduce un DNI v�lido.\n";
        }
    } while (!validarDNI(dni));
    do {
        std::cout << "Introduce el nombre: ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            std::cerr << "Error: El nombre no puede estar vac�o. Por favor, introduce un nombre v�lido.\n";
        }
    } while (nombre.empty());

    do {
        std::cout << "Introduce la edad: ";
        if (!obtenerEntrada(edad) || !validarEdad(edad)) {
            std::cerr << "Por favor, introduce una edad v�lida (mayor que 0).\n";
        }
        else {
            break;
        }
    } while (!validarEdad(edad));

    do {
        std::cout << "Introduce el n�mero de tel�fono (9 d�gitos): ";
        std::getline(std::cin, telefono);
        if (!validarTelefono(telefono)) {
            std::cerr << "Por favor, introduce un n�mero de tel�fono v�lido.\n";
        }
    } while (!validarTelefono(telefono));

    std::cout << "Introduce la direcci�n: ";
    std::getline(std::cin, direccion);

    do {
        std::cout << "Introduce el email (formato v�lido): ";
        std::getline(std::cin, email);
        if (!validarEmail(email)) {
            std::cerr << "Por favor, introduce un email v�lido.\n";
        }
    } while (!validarEmail(email));
}

// Mostrar los datos de la persona
void Person::showPersonData() const {
    std::cout << "DNI: " << dni << ", Nombre: " << nombre
        << ", Edad: " << edad << ", Tel�fono: " << telefono
        << ", Direcci�n: " << direccion << ", Email: " << email << std::endl;
}
