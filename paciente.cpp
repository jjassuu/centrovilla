#include "paciente.h"
#include <iomanip>

// Constructor de la clase Paciente
Paciente::Paciente(const std::string& dni, const std::string& nombre, int edad,
    const std::string& telefono, const std::string& direccion,
    const std::string& email, const std::string& dolencia, const std::string& fechaCita)
    : dni(dni), nombre(nombre), edad(edad), telefono(telefono), direccion(direccion),
    email(email), dolencia(dolencia), diacita(fechaCita) {}

// Registrar un nuevo paciente.
void Paciente::registrarPaciente() {
    std::cout << "Introduce el DNI del paciente\n";
    std::cin >> dni;
    std::cin.ignore();

    std::cout << "Introduce el nombre: ";
    std::getline(std::cin, nombre);

    std::cout << "Introduce la edad: ";
    std::cin >> edad;
    std::cin.ignore();

    std::cout << "Introduce el teléfono: ";
    std::getline(std::cin, telefono);

    std::cout << "Introduce la dirección: ";
    std::getline(std::cin, direccion);

    std::cout << "Introduce el correo electrónico: ";
    std::getline(std::cin, email);

    std::cout << "Introduce la dolencia: ";
    std::getline(std::cin, dolencia);

    std::cout << "Introduce la fecha de la cita (YYYY-MM-DD): ";
    std::cin >> diacita;

    guardarEnArchivo();
    std::cout << "\nPaciente registrado con éxito.\n";
}

// Guardar paciente en el archivo.
void Paciente::guardarEnArchivo() const {
    std::ofstream archivo("pacientes.csv", std::ios::app);
    if (archivo.is_open()) {
        archivo<< dni << "," << nombre << "," << edad << "," << telefono
            << "," << direccion << "," << email << "," << dolencia
            << "," << diacita << "\n";
        archivo.close();
    }
    else {
        std::cerr << "Error al abrir el archivo para guardar.\n";
    }
}

// Listar todos los pacientes.
void Paciente::listarPacientes() {
    std::ifstream archivo("pacientes.csv");
    if (archivo.is_open()) {
        std::string linea;
        std::cout << "-Listado de pacientes-\n";
        while (std::getline(archivo, linea)) {
            std::cout << linea << "\n";
        }
        archivo.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo\n";
    }
}

// Buscar un paciente por ID.
void Paciente::buscarPaciente(const std::string& dni) {
    std::ifstream archivo("pacientes.csv");
    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string campo;
            std::getline(ss, campo, ','); // Leer el DNI

            if (campo == dni) {
                std::cout << "Paciente encontrado: " << linea << "\n";
                archivo.close();
                return;
            }
        }
        std::cout << "Paciente con DNI " << dni << " no encontrado.\n";
        archivo.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo para buscar al paciente.\n";
    }
}


// Eliminar paciente
void Paciente::eliminarPaciente(int id) {
    std::ifstream archivo("pacientes.csv");
    std::ofstream temp("temp.csv");

    if (archivo.is_open() && temp.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string campo;
            std::getline(ss, campo, ','); // Leer el DNI

            if (std::stoi(campo) != id) {
                temp << linea << "\n";
            }
        }

        archivo.close();
        temp.close();

        std::remove("pacientes.csv");
        std::rename("temp.csv", "pacientes.csv");
        std::cout << "Paciente con ID " << id << " eliminado correctamente.\n";
    }
    else {
        std::cerr << "Error al abrir los archivos para eliminar al paciente.\n";
    }
}