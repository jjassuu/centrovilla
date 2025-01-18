#include "doctor.h"
#include "person.h"
#include <iostream>
#include <fstream>
#include <sstream>


void Doctor::registrarDoctor() {
    std::cout << "Iniciando registro de doctor...\n";
    // Llamar a los datos heredados de Person
    getPersonData();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Introduce la especialización médica (Médico de familia, Pediatra, Enfermero): ";
    std::getline(std::cin, especialidad);
    std::cout << "Especialización registrada: " << especialidad << "\n";

    std::cout << "Introduce la disponibilidad (Mañana/Tarde): ";
    std::getline(std::cin, disponibilidad);
    std::cout << "Disponibilidad registrada: " << disponibilidad << "\n";

    guardarDoctor();
    std::cout << "Doctor registrado con éxito.\n";
}

void Doctor::mostrarDoctor() const {
    // Mostrar datos generales de la persona
    showPersonData();

    // Mostrar información adicional del doctor
    std::cout << "Especialización: " << especialidad << ", Disponibilidad: " << disponibilidad << std::endl;
}
void Doctor::guardarDoctor() const {
    std::ofstream file("doctor.csv", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo 'doctor.csv' para guardar.\n";
        return;
    }
    file << dni << "," << nombre << "," << edad << ","
        << telefono << "," << direccion << "," << email << ","
        << especialidad << "," << disponibilidad << "\n";
    file.close();
 }
   
 
void Doctor::listarDoctores() {
    std::ifstream file("doctor.csv");
    if (file.is_open()) {
        std::string linea;
        std::cout << "\n--- Lista de Doctores ---\n";
        while (std::getline(file, linea)) {
            std::cout << linea << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Error al abrir el archivo CSV de doctores.\n";
    }
}

void Doctor::eliminarDoctor(const std::string& dni) {
    std::ifstream archivo("doctor.csv");
    std::ofstream temp("temp.csv");

    if (!archivo.is_open() || !temp.is_open()) {
        std::cerr << "Error al abrir los archivos para eliminar al doctor.\n";
        return;
    }

    std::string linea;
    bool encontrado = false;
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string campoDNI;
        std::getline(ss, campoDNI, ','); // Leer el DNI

        if (campoDNI == dni) {
            encontrado = true; // Doctor encontrado, no lo copiamos al archivo temporal
        }
        else {
            temp << linea << "\n";
        }
    }

    archivo.close();
    temp.close();

    if (encontrado) {
        std::remove("doctor.csv");
        if (std::rename("temp.csv", "doctor.csv") == 0) {
            std::cout << "Doctor con DNI " << dni << " eliminado correctamente.\n";
        }
        else {
            std::cerr << "Error al renombrar el archivo temporal a 'doctor.csv'.\n";
        }
    }
    else {
        std::cerr << "Doctor con DNI " << dni << " no encontrado.\n";
        std::remove("temp.csv");
    }
}

void Doctor::editarDoctor(const std::string& dni) {
    std::ifstream archivo("doctor.csv");
    std::ofstream temp("temp.csv");

    if (!archivo.is_open() || !temp.is_open()) {
        std::cerr << "Error al abrir los archivos para editar al doctor.\n";
        return;
    }

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string campoDNI, campoNombre, campoEdad, campoTelefono, campoDireccion, campoEmail, campoEspecialidad, campoDisponibilidad;

        // Leer los campos de la línea
        std::getline(ss, campoDNI, ',');
        std::getline(ss, campoNombre, ',');
        std::getline(ss, campoEdad, ',');
        std::getline(ss, campoTelefono, ',');
        std::getline(ss, campoDireccion, ',');
        std::getline(ss, campoEmail, ',');
        std::getline(ss, campoEspecialidad, ',');
        std::getline(ss, campoDisponibilidad, ',');

        if (campoDNI == dni) {
            encontrado = true;

          
            std::cout << "Datos actuales del doctor con DNI " << dni << ":\n";
            std::cout << "Nombre: " << campoNombre << "\n";
            std::cout << "Edad: " << campoEdad << "\n";
            std::cout << "Teléfono: " << campoTelefono << "\n";
            std::cout << "Dirección: " << campoDireccion << "\n";
            std::cout << "Email: " << campoEmail << "\n";
            std::cout << "Especialidad: " << campoEspecialidad << "\n";
            std::cout << "Disponibilidad: " << campoDisponibilidad << "\n";

            std::cout << "\nIntroduce los nuevos datos (deja en blanco para mantener los actuales):\n";

            std::string nuevoNombre = campoNombre;
            do {
                std::cout << "Nombre [" << campoNombre << "]: ";
                std::getline(std::cin, nuevoNombre);
                if (!nuevoNombre.empty()) {
                    break; // Si el nombre no está vacío, se acepta
                }
                else {
                    std::cout << "El nombre no puede estar vacío. Inténtalo de nuevo.\n";
                }
            } while (true);


            int nuevaEdad = std::stoi(campoEdad);
            do {
                std::cout << "Edad [" << campoEdad << "]: ";
                std::string entradaEdad;
                std::getline(std::cin, entradaEdad);
                if (entradaEdad.empty()) break;
                try {
                    nuevaEdad = std::stoi(entradaEdad);
                    if (nuevaEdad > 0) break;
                }
                catch (...) {
                    std::cerr << "Por favor, introduce una edad válida.\n";
                }
            } while (true);

            std::string nuevoTelefono = campoTelefono;
            do {
                std::cout << "Teléfono [" << campoTelefono << "]: ";
                std::string entradaTelefono;
                std::getline(std::cin, entradaTelefono);
                if (entradaTelefono.empty()) break;
                if (entradaTelefono.length() == 9) {
                    nuevoTelefono = entradaTelefono;
                    break;
                }
                else {
                    std::cerr << "Por favor, introduce un número de teléfono válido (9 dígitos).\n";
                }
            } while (true);

            std::cout << "Dirección [" << campoDireccion << "]: ";
            std::string nuevaDireccion;
            std::getline(std::cin, nuevaDireccion);
            if (nuevaDireccion.empty()) nuevaDireccion = campoDireccion;

            std::cout << "Email [" << campoEmail << "]: ";
            std::string nuevoEmail;
            std::getline(std::cin, nuevoEmail);
            if (nuevoEmail.empty()) nuevoEmail = campoEmail;

            std::cout << "Especialidad [" << campoEspecialidad << "]: ";
            std::string nuevaEspecialidad;
            std::getline(std::cin, nuevaEspecialidad);
            if (nuevaEspecialidad.empty()) nuevaEspecialidad = campoEspecialidad;

            std::cout << "Disponibilidad [" << campoDisponibilidad << "]: ";
            std::string nuevaDisponibilidad;
            std::getline(std::cin, nuevaDisponibilidad);
            if (nuevaDisponibilidad.empty()) nuevaDisponibilidad = campoDisponibilidad;

            temp << campoDNI << "," << nuevoNombre << "," << nuevaEdad << ","
                << nuevoTelefono << "," << nuevaDireccion << "," << nuevoEmail << ","
                << nuevaEspecialidad << "," << nuevaDisponibilidad << "\n";
        }
        else {
            temp << linea << "\n";
        }
    }

    archivo.close();
    temp.close();

    if (encontrado) {
        std::remove("doctor.csv");
        std::rename("temp.csv", "doctor.csv");
        std::cout << "Datos del doctor actualizados correctamente.\n";
    }
    else {
        std::cerr << "Doctor con DNI " << dni << " no encontrado.\n";
        std::remove("temp.csv");
    }
}
