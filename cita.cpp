#include "cita.h"

GestionCitas::GestionCitas() {
    cargarCitasDesdeArchivo();
}

bool GestionCitas::verificarDisponibilidad(const std::string& dniDoctor, const std::string& fecha, const std::string& hora) {
    for (const auto& cita : citas) {
        if (cita.dniDoctor == dniDoctor && cita.fecha == fecha && cita.hora == hora) {
            return false;
        }
    }
    return true;
}

bool GestionCitas::validarFecha(const std::string& fecha) {
    std::regex formatoFecha("^\\d{4}-\\d{2}-\\d{2}$");
    return std::regex_match(fecha, formatoFecha);
}

bool GestionCitas::validarHora(const std::string& hora) {
    std::regex formatoHora("^([01]\\d|2[0-3]):[0-5]\\d$");
    return std::regex_match(hora, formatoHora);
}

bool GestionCitas::solicitarDNI(const std::string& tipo, std::string& dni) {
    do {
        std::cout << "Introduce el DNI del " << tipo << ": ";
        std::cin >> dni;

        if (!Person::validarDNI(dni)) {
            std::cerr << "Error: Formato de DNI invalido. Debe tener 8 numeros y 1 letra (ejemplo: 12345678A).\n";
            continue;
        }

        if ((tipo == "Paciente" && !Paciente::existePaciente(dni)) ||
            (tipo == "Doctor" && !Doctor::existeDoctor(dni))) {
            std::cerr << "Error: El " << tipo << " con DNI " << dni << " no esta registrado.\n";
            continue;
        }

        return true;
    } while (true);
}

bool GestionCitas::solicitarFecha(std::string& fecha) {
    do {
        std::cout << "Introduce la Fecha (YYYY-MM-DD): ";
        std::cin >> fecha;

        if (!validarFecha(fecha)) {
            std::cerr << "Error: Formato de fecha invalido. Ejemplo: 2025-01-19.\n";
        }
        else {
            return true;
        }
    } while (true);
}

bool GestionCitas::solicitarHora(std::string& hora) {
    do {
        std::cout << "Introduce la Hora (HH:MM): ";
        std::cin >> hora;

        if (!validarHora(hora)) {
            std::cerr << "Error: Formato de hora invalido. Ejemplo: 14:30.\n";
        }
        else {
            return true;
        }
    } while (true);
}

bool GestionCitas::solicitarEspecialidad(std::string& especialidad) {
    do {
        std::cout << "Introduce la Especialidad (Medico de familia, Pediatra, Enfermero): ";
        std::getline(std::cin >> std::ws, especialidad); // Leer eliminando espacios iniciales

        if (especialidad != "Medico de familia" && especialidad != "Pediatra" && especialidad != "Enfermero") {
            std::cerr << "Error: Especialidad invalida. Debe ser Medico de familia, Pediatra o Enfermero.\n";
        }
        else {
            return true;
        }
    } while (true);
}

void GestionCitas::agendarCita(const std::string& dniPaciente, const std::string& dniDoctor, const std::string& fecha, const std::string& hora, const std::string& especialidad) {
    std::string dniPacienteTemp = dniPaciente, dniDoctorTemp = dniDoctor;
    std::string fechaTemp = fecha, horaTemp = hora, especialidadTemp = especialidad;

    if (!solicitarDNI("Paciente", dniPacienteTemp)) {
        std::cerr << "Error: No se puede proceder sin un DNI de paciente valido.\n";
        return;
    }

    if (!solicitarDNI("Doctor", dniDoctorTemp)) {
        std::cerr << "Error: No se puede proceder sin un DNI de doctor valido.\n";
        return;
    }

    if (!solicitarFecha(fechaTemp)) {
        std::cerr << "Error: No se puede proceder sin una fecha valida.\n";
        return;
    }

    if (!solicitarHora(horaTemp)) {
        std::cerr << "Error: No se puede proceder sin una hora valida.\n";
        return;
    }

    if (!solicitarEspecialidad(especialidadTemp)) {
        std::cerr << "Error: No se puede proceder sin una especialidad valida.\n";
        return;
    }

    if (!verificarDisponibilidad(dniDoctorTemp, fechaTemp, horaTemp)) {
        std::cerr << "Error: El doctor no esta disponible en la fecha y hora indicadas.\n";
        return;
    }

    Cita nuevaCita = { fechaTemp, horaTemp, dniPacienteTemp, dniDoctorTemp, especialidadTemp };
    citas.push_back(nuevaCita);
    guardarCitasEnArchivo();
    std::cout << "Cita agendada exitosamente.\n";
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

void GestionCitas::listarCitasPorDia(const std::string& fecha) const {
    std::cout << "Citas para el dia " << fecha << ":\n";
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

    std::cout << "Reporte de citas para el dia " << fecha << ":\n";
    for (const auto& [especialidad, count] : especialidadesCount) {
        std::cout << "Especialidad: " << especialidad << ", Cantidad: " << count << "\n";
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
        if ((turno == "dia" && cita.hora < "12:00") || (turno == "tarde" && cita.hora >= "12:00")) {
            std::cout << "Fecha: " << cita.fecha << ", Hora: " << cita.hora
                << ", Paciente: " << cita.dniPaciente
                << ", Doctor: " << cita.dniDoctor
                << ", Especialidad: " << cita.especialidad << "\n";
        }
    }
}

void GestionCitas::modificarCita(const std::string& dniPaciente, const std::string& fechaActual, const std::string& horaActual) {
    std::string dniPacienteTemp = dniPaciente;
    std::string fechaActualTemp = fechaActual;
    std::string horaActualTemp = horaActual;

    do {
        if (!Paciente::validarDNI(dniPacienteTemp)) {
            std::cerr << "Error: Formato de DNI invalido. Debe tener 8 numeros y 1 letra (ejemplo: 12345678A).\n";
            std::cout << "Introduce el DNI del Paciente: ";
            std::cin >> dniPacienteTemp;
            continue;
        }

        if (!Paciente::existePaciente(dniPacienteTemp)) {
            std::cerr << "Error: El paciente con DNI " << dniPacienteTemp << " no esta registrado.\n";
            std::cout << "Introduce el DNI del Paciente: ";
            std::cin >> dniPacienteTemp;
            continue;
        }

        break;
    } while (true);

    do {
        if (!validarFecha(fechaActualTemp)) {
            std::cerr << "Error: Formato de fecha invalido. Debe ser YYYY-MM-DD.\n";
            std::cout << "Introduce la Fecha actual de la cita (YYYY-MM-DD): ";
            std::cin >> fechaActualTemp;
            continue;
        }
        break;
    } while (true);

    do {
        if (!validarHora(horaActualTemp)) {
            std::cerr << "Error: Formato de hora invalido. Debe ser HH:MM.\n";
            std::cout << "Introduce la Hora actual de la cita (HH:MM): ";
            std::cin >> horaActualTemp;
            continue;
        }
        break;
    } while (true);

    bool encontrada = false;
    for (auto& cita : citas) {
        if (cita.dniPaciente == dniPacienteTemp && cita.fecha == fechaActualTemp && cita.hora == horaActualTemp) {
            encontrada = true;

            std::cout << "Cita encontrada:\n";
            std::cout << "Fecha actual: " << cita.fecha << ", Hora actual: " << cita.hora << "\n";

            std::string nuevaFecha, nuevaHora;

            std::cout << "Introduce la nueva fecha (YYYY-MM-DD) o deja en blanco para mantener: ";
            std::getline(std::cin >> std::ws, nuevaFecha);

            if (!nuevaFecha.empty()) {
                if (validarFecha(nuevaFecha)) {
                    cita.fecha = nuevaFecha;
                }
                else {
                    std::cerr << "Error: Formato de fecha invalido. Manteniendo la fecha actual.\n";
                }
            }

            std::cout << "Introduce la nueva hora (HH:MM) o deja en blanco para mantener: ";
            std::getline(std::cin >> std::ws, nuevaHora);

            if (!nuevaHora.empty()) {
                if (validarHora(nuevaHora)) {
                    if (verificarDisponibilidad(cita.dniDoctor, cita.fecha, nuevaHora)) {
                        cita.hora = nuevaHora;
                    }
                    else {
                        std::cerr << "Error: El doctor no esta disponible en la nueva hora. Manteniendo la hora actual.\n";
                    }
                }
                else {
                    std::cerr << "Error: Formato de hora invalido. Manteniendo la hora actual.\n";
                }
            }

            guardarCitasEnArchivo();
            std::cout << "Cita modificada exitosamente.\n";
            return;
        }
    }

    if (!encontrada) {
        std::cerr << "Error: No se encontro ninguna cita con los datos proporcionados.\n";
    }
}


void GestionCitas::eliminarCita(const std::string& dniPaciente, const std::string& fecha, const std::string& hora) {
    bool encontrada = false;

    for (auto it = citas.begin(); it != citas.end(); ++it) {
        if (it->dniPaciente == dniPaciente && it->fecha == fecha && it->hora == hora) {
            citas.erase(it);
            encontrada = true;
            guardarCitasEnArchivo(); // Actualizar el archivo despues de eliminar
            std::cout << "Cita eliminada exitosamente.\n";
            return;
        }
    }

    if (!encontrada) {
        std::cerr << "Error: No se encontro ninguna cita con los datos proporcionados.\n";
    }
}
