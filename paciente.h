#ifndef PACIENTE_H
#define PACIENTE_H

#include "person.h"
#include "cita.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <random>
using namespace std;

struct Dolencia {
    string fecha;
    string descripcion;
    string medico;
};
class Paciente : public Person {
private:

public:
    Paciente(const std::string& dni = "", const std::string& nombre = "", int edad = 0,
        const std::string& telefono = "", const std::string& direccion = "",
        const std::string& email = "");

    // Métodos
    void registrarPaciente();
    static void listarPacientes();
    static void buscarPaciente(const std::string& dni);
    void guardarEnArchivo() const;
    static void eliminarPaciente(const std::string& dni);
    static bool existePaciente(const std::string& dni); // Verifica si el DNI ya está registrado
    void editarPaciente(const std::string& dni);
    std::string derivarPaciente(const std::string& centro);

    // Métodos para el historial de dolencias
    void agregarDolencia(const std::string& dni, const std::string& fecha, const std::string& descripcion, const std::string& medico);
    void mostrarHistorialDolencias( const std::string& dni) ;
};

#endif
