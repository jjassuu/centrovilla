#ifndef PACIENTE_H
#define PACIENTE_H

#include "person.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <random>
using namespace std;


class Paciente : public Person {
private:
    string dni;
    string nombre;
    int edad;
    string telefono;
    string direccion;
    string email;
    string dolencia;
    string diacita;

public:
    Paciente(const std::string& dni = "", const std::string& nombre = "", int edad = 0,
        const std::string& telefono = "", const std::string& direccion = "",
        const std::string& email = "", const std::string& dolencia = "", const std::string& fechaCita = "");

    // Métodos
    void registrarPaciente();
    static void listarPacientes();
    static void buscarPaciente(const std::string& dni);
    void guardarEnArchivo() const;
    static void eliminarPaciente(int id);
};

#endif
