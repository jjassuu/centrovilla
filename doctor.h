#ifndef DOCTOR_H
#define DOCTOR_H

#include "person.h"  // Asegúrate de que este encabezado está correctamente incluido
#include <string>
#include <fstream>
#include <iostream>

class Doctor : public Person {
private:
    std::string especialidad;
    std::string disponibilidad;

public:
    Doctor(const std::string& dni = "", const std::string& nombre = "", int edad = 0,
        const std::string& telefono = "", const std::string& direccion = "",
        const std::string& email = "", const std::string& especialidad = "",
        const std::string& disponibilidad = "")
        : Person(dni, nombre, edad, telefono, direccion, email),
        especialidad(especialidad), disponibilidad(disponibilidad) {}

    void registrarDoctor();
    void mostrarDoctor() const;
    void guardarDoctor() const;
    static void listarDoctores();
    static void eliminarDoctor(const std::string& dni);
};

#endif
