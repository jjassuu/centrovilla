#include "person.h"
#include <regex>
#include <iostream>
#include "main.h"
#include "paciente.h"
// Validar el formato del DNI
bool Person::validarDNI(const std::string& dni) {
    std::regex formatoDNI("^\\d{8}[A-Za-z]$");
    if (!std::regex_match(dni, formatoDNI)) {
        std::cerr << "Error: El DNI debe tener 8 numeros seguidos de una letra.\n";
        return false;
    }
    return true;
}

// Validar la edad
bool Person::validarEdad(int edad) {
    if (edad <= 0) {
        std::cerr << "Error: La edad debe ser un numero positivo.\n";
        return false;
    }
    return true;
}

// Validar el formato del correo electronico
bool Person::validarEmail(const std::string& email) {
    std::regex patronEmail(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!std::regex_match(email, patronEmail)) {
        std::cerr << "Error: El email no tiene un formato valido.\n";
        return false;
    }
    return true;
}

// Validar el formato del numero de telefono (9 digitos)
bool Person::validarTelefono(const std::string& telefono) {
    std::regex patronTelefono("^\\d{9}$");
    if (!std::regex_match(telefono, patronTelefono)) {
        std::cerr << "Error: El telefono debe contener exactamente 9 digitos.\n";
        return false;
    }
    return true;
}

// Solicitar datos de la persona desde la consola
void Person::getPersonData() {
    do {
        std::cout << "Introduce el DNI (8 numeros seguidos de una letra): ";
        std::getline(std::cin, dni);
        dni = convertirAMayusculas(dni);
        if (!validarDNI(dni)) {
            std::cerr << "Por favor, introduce un DNI valido.\n";
        }
        else if (Paciente::existePaciente(dni)) {
            std::cerr << "Error: El paciente con DNI " << dni << " ya esta registrado.\n";
            throw std::runtime_error("Paciente ya registrado.");
        }
        else {
            break;
        }
    } while (true);
    do {
        std::cout << "Introduce el nombre: ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            std::cerr << "Error: El nombre no puede estar vacio. Por favor, introduce un nombre valido.\n";
        }
    } while (nombre.empty());

    do {
        std::cout << "Introduce la edad: ";
        std::string entradaEdad;
        std::getline(std::cin, entradaEdad);

        if (entradaEdad.empty()) {
            std::cerr << "Error: La edad no puede estar vacia. Por favor, introduce una edad valida.\n";
            continue;
        }

        try {
            edad = std::stoi(entradaEdad);
            if (edad <= 0) {
                throw std::invalid_argument("Edad no valida");
            }
            break;
        }
        catch (...) {
            std::cerr << "Error: La edad debe ser un numero mayor que 0. Por favor, intentalo de nuevo.\n";
        }
    } while (true);

        

    do {
        std::cout << "Introduce el numero de telefono (9 digitos): ";
        std::getline(std::cin, telefono);
        if (!validarTelefono(telefono)) {
            std::cerr << "Por favor, introduce un numero de telefono valido.\n";
        }
    } while (!validarTelefono(telefono));

    do {
        std::cout << "Introduce la direccion: ";
        std::getline(std::cin, direccion);

        if (direccion.empty()) {
            std::cerr << "Error: La direccion no puede estar vacia. Por favor, introduce una direccion valida.\n";
        }
        else {
            break;
        }
    } while (true);


    do {
        std::cout << "Introduce el email (formato valido): ";
        std::getline(std::cin, email);
        if (!validarEmail(email)) {
            std::cerr << "Por favor, introduce un email valido.\n";
        }
    } while (!validarEmail(email));
}

// Mostrar los datos de la persona
void Person::showPersonData() const {
    std::cout << "DNI: " << dni << ", Nombre: " << nombre
        << ", Edad: " << edad << ", Telefono: " << telefono
        << ", Direccion: " << direccion << ", Email: " << email << std::endl;
}
