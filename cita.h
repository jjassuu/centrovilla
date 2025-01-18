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

    void agendarCita(const std::string& dniPaciente, const std::string& dniDoctor, const std::string& fecha, const std::string& hora, const std::string& especialidad);
    void listarCitasPorDia(const std::string& fecha) const;
    void generarReportePorDia(const std::string& fecha) const;
    void mostrarTodasLasCitas() const;
    void listarCitasPorTurno(const std::string& turno) const; // Turno: "mañana" o "tarde"
};

#endif
