#include "doctor.h"
#include "person.h"
#include <iostream>
#include <fstream>

void Doctor::registrarDoctor() {
    std::cout << "Iniciando registro de doctor...\n";
    // Llamar a los datos heredados de Person
    getPersonData();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Introduce la especialización médica (Médico de familia, Pediatra, Enfermero): ";
    std::getline(std::cin, especialidad);
    std::cout << "Especialización registrada: " << especialidad << "\n";

    std::cout << "Introduce la disponibilidad (Mañana/Tarde): ";
    std::getline(std::cin, disponibilidad);
    std::cout << "Disponibilidad registrada: " << disponibilidad << "\n";

    guardarDoctor();
    std::cout << "Doctor registrado con éxito.\n";
}

void Doctor::mostrarDoctor() const {
    // Mostrar datos generales de la persona
    showPersonData();

    // Mostrar información adicional del doctor
    std::cout << "Especialización: " << especialidad << ", Disponibilidad: " << disponibilidad << std::endl;
}
void Doctor::guardarDoctor() const {
    std::ofstream file("doctor.csv", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo 'doctor.csv' para guardar.\n";
        return;
    }
    file << dni << "," << nombre << "," << edad << ","
        << telefono << "," << direccion << "," << email << ","
        << especialidad << "," << disponibilidad << "\n";
    file.close();
 }
   
 
void Doctor::listarDoctores() {
    std::ifstream file("doctor.csv");
    if (file.is_open()) {
        std::string linea;
        std::cout << "\n--- Lista de Doctores ---\n";
        while (std::getline(file, linea)) {
            std::cout << linea << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Error al abrir el archivo CSV de doctores.\n";
    }
}
