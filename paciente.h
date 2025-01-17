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

struct Dolencia {
    string fecha;
    string descripcion;
    string medico;
};
class Paciente : public Person {
private:
    string dni;
    string nombre;
    int edad;
    string telefono;
    string direccion;
    string email;
    vector <Dolencia> historialDolencias;
    string diacita;

public:
    Paciente(const std::string& dni = "", const std::string& nombre = "", int edad = 0,
        const std::string& telefono = "", const std::string& direccion = "",
        const std::string& email = "", const std::string& fechaCita = "");

    // Métodos
    void registrarPaciente();
    static void listarPacientes();
    static void buscarPaciente(const std::string& dni);
    void guardarEnArchivo() const;
    static void eliminarPaciente(const std::string& dni);

    // Métodos para el historial de dolencias
    void agregarDolencia(const std::string& dni, const std::string& fecha, const std::string& descripcion, const std::string& medico);
    void mostrarHistorialDolencias( const std::string& dni) ;
};

#endif
