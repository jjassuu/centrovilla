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

    // M�todos
    void registrarPaciente();
    static void listarPacientes();
    static void buscarPaciente(const std::string& dni);
    void guardarEnArchivo() const;
    static void eliminarPaciente(const std::string& dni);
    static bool validarDNI(const std::string& dni);
    static bool existePaciente(const std::string& dni); // Verifica si el DNI ya est� registrado
    void editarPaciente(const std::string& dni);
    std::string derivarPaciente(const std::string& centro);

    // M�todos para el historial de dolencias
    void agregarDolencia(const std::string& dni, const std::string& fecha, const std::string& descripcion, const std::string& medico);
    void mostrarHistorialDolencias( const std::string& dni) ;
};

#endif
