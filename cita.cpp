#include "cita.h"

bool GestionCitas::verificarDisponibilidad(const std::string& dniDoctor, const std::string& fecha, const std::string& hora) {
    for (const auto& cita : citas) {
        if (cita.dniDoctor == dniDoctor && cita.fecha == fecha && cita.hora == hora) {
            return false;
        }
    }
    return true;
}

void GestionCitas::cargarCitasDesdeArchivo() {
    std::ifstream archivo("citas.csv");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo de citas.\n";
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        Cita cita;
        std::getline(ss, cita.fecha, ',');
        std::getline(ss, cita.hora, ',');
        std::getline(ss, cita.dniPaciente, ',');
        std::getline(ss, cita.dniDoctor, ',');
        std::getline(ss, cita.especialidad, ',');
        citas.push_back(cita);
    }
    archivo.close();
}

void GestionCitas::guardarCitasEnArchivo() const {
    std::ofstream archivo("citas.csv", std::ios::trunc);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar citas.\n";
        return;
    }

    for (const auto& cita : citas) {
        archivo << cita.fecha << "," << cita.hora << "," << cita.dniPaciente << ","
            << cita.dniDoctor << "," << cita.especialidad << "\n";
    }
    archivo.close();
}

GestionCitas::GestionCitas() {
    cargarCitasDesdeArchivo();
}

void GestionCitas::agendarCita(const std::string& dniPaciente, const std::string& dniDoctor, const std::string& fecha, const std::string& hora, const std::string& especialidad) {
    if (!verificarDisponibilidad(dniDoctor, fecha, hora)) {
        std::cerr << "El doctor no está disponible en esta fecha y hora.\n";
        return;
    }

    if (especialidad == "Enfermero" && hora >= "12:00") {
        std::cerr << "Los enfermeros solo pueden trabajar en el turno de mañana.\n";
        return;
    }

    Cita nuevaCita = { fecha, hora, dniPaciente, dniDoctor, especialidad };
    citas.push_back(nuevaCita);
    guardarCitasEnArchivo();
    std::cout << "Cita agendada exitosamente.\n";
}

void GestionCitas::listarCitasPorDia(const std::string& fecha) const {
    std::cout << "Citas para el día " << fecha << ":\n";
    for (const auto& cita : citas) {
        if (cita.fecha == fecha) {
            std::cout << "Hora: " << cita.hora
                << ", Paciente: " << cita.dniPaciente
                << ", Doctor: " << cita.dniDoctor
                << ", Especialidad: " << cita.especialidad << "\n";
        }
    }
}

void GestionCitas::generarReportePorDia(const std::string& fecha) const {
    std::map<std::string, int> especialidadesCount;
    for (const auto& cita : citas) {
        if (cita.fecha == fecha) {
            especialidadesCount[cita.especialidad]++;
        }
    }

    std::cout << "Reporte de citas para el día " << fecha << ":\n";
    for (const auto& [especialidad, count] : especialidadesCount) {
        std::cout << "Especialidad: " << especialidad << ", Cantidad de citas: " << count << "\n";
    }
}

void GestionCitas::mostrarTodasLasCitas() const {
    std::cout << "Todas las citas registradas:\n";
    for (const auto& cita : citas) {
        std::cout << "Fecha: " << cita.fecha << ", Hora: " << cita.hora
            << ", Paciente: " << cita.dniPaciente
            << ", Doctor: " << cita.dniDoctor
            << ", Especialidad: " << cita.especialidad << "\n";
    }
}

void GestionCitas::listarCitasPorTurno(const std::string& turno) const {
    std::cout << "Citas para el turno de " << turno << ":\n";
    for (const auto& cita : citas) {
        if ((turno == "mañana" && cita.hora < "12:00") || (turno == "tarde" && cita.hora >= "12:00")) {
            std::cout << "Fecha: " << cita.fecha << ", Hora: " << cita.hora
                << ", Paciente: " << cita.dniPaciente
                << ", Doctor: " << cita.dniDoctor
                << ", Especialidad: " << cita.especialidad << "\n";
        }
    }
}
