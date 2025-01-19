#ifndef CITA_H
#define CITA_H

#include "paciente.h"
#include "doctor.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <regex>

struct Cita {
    std::string fecha;
    std::string hora;
    std::string dniPaciente;
    std::string dniDoctor;
    std::string especialidad;
};

class GestionCitas {
private:
    std::vector<Cita> citas;

    bool verificarDisponibilidad(const std::string& dniDoctor, const std::string& fecha, const std::string& hora);
    void cargarCitasDesdeArchivo();
    void guardarCitasEnArchivo() const;

public:
    GestionCitas();
    static bool validarFecha(const std::string& fecha);
    static bool validarHora(const std::string& hora);
    bool solicitarDNI(const std::string& tipo, std::string& dni);
    bool solicitarFecha(std::string& fecha);
    bool solicitarHora(std::string& hora);
    bool solicitarEspecialidad(std::string& especialidad);
    void agendarCita(const std::string& dniPaciente, const std::string& dniDoctor, const std::string& fecha, const std::string& hora, const std::string& especialidad);
    void listarCitasPorDia(const std::string& fecha) const;
    void generarReportePorDia(const std::string& fecha) const;
    void mostrarTodasLasCitas() const;
    void listarCitasPorTurno(const std::string& turno) const;
    void modificarCita(const std::string& dniPaciente, const std::string& fechaActual, const std::string& horaActual);
    void eliminarCita(const std::string& dniPaciente, const std::string& fecha, const std::string& hora);

};

#endif
