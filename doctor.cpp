#include "doctor.h"
#include "person.h"
#include <iostream>
#include "main.h"
#include <fstream>
#include <sstream>


void Doctor::registrarDoctor() {
    std::cout << "Iniciando registro de doctor...\n";
    do {
        std::cout << "Introduce el DNI (8 números seguidos de una letra): ";
        std::getline(std::cin, dni);
        dni = convertirAMayusculas(dni); // Convierte el DNI a mayúsculas para consistencia

        if (!validarDNI(dni)) {
            std::cerr << "Error: Por favor, introduce un DNI válido.\n";
        }
        else if (existeDoctor(dni)) { // Aquí se usa Doctor::existeDoctor
            std::cerr << "Error: El doctor con DNI " << dni << " ya está registrado.\n";
        }
        else {
            break; // DNI válido y no registrado
        }
    } while (true);

    do {
        std::cout << "Introduce el nombre: ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            std::cerr << "Error: El nombre no puede estar vacío. Por favor, introduce un nombre válido.\n";
        }
    } while (nombre.empty());

    do {
        std::cout << "Introduce la edad: ";
        if (!obtenerEntrada(edad) || !validarEdad(edad)) {
            std::cerr << "Por favor, introduce una edad válida (mayor que 0).\n";
        }
        else {
            break;
        }
    } while (!validarEdad(edad));

    do {
        std::cout << "Introduce el número de teléfono (9 dígitos): ";
        std::getline(std::cin, telefono);
        if (!validarTelefono(telefono)) {
            std::cerr << "Por favor, introduce un número de teléfono válido.\n";
        }
    } while (!validarTelefono(telefono));

    std::cout << "Introduce la dirección: ";
    std::getline(std::cin, direccion);

    do {
        std::cout << "Introduce el email (formato válido): ";
        std::getline(std::cin, email);
        if (!validarEmail(email)) {
            std::cerr << "Por favor, introduce un email válido.\n";
        }
    } while (!validarEmail(email));

    do {
        std::cout << "Introduce la especializacion medica (Medico de familia, Pediatra, Enfermero): ";
        std::getline(std::cin, especialidad);

        if (especialidad == "Medico de familia" || especialidad == "Pediatra" || especialidad == "Enfermero") {
            std::cout << "Especializacion registrada: " << especialidad << "\n";
            break;
        }
        else {
            std::cerr << "Error: Especialización invalida. Debe ser Medico de familia, Pediatra, Enfermero.\n";
        }
    } while (true);

    do {
        std::cout << "Introduce la disponibilidad (Dia/Tarde): ";
        std::getline(std::cin, disponibilidad);

        if (disponibilidad == "Dia") {
            std::cout << "Disponibilidad registrada: Dia (9:00 - 14:00)\n";
            break;
        }
        else if (disponibilidad == "Tarde") {
            std::cout << "Disponibilidad registrada: Tarde (15:00 - 19:00)\n";
            break;
        }
        else {
            std::cerr << "Error: Disponibilidad invalida. Debe ser Dia o Tarde.\n";
        }
    } while (true);

    guardarDoctor();
    std::cout << "Doctor registrado con exito.\n";
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

bool Doctor::existeDoctor(const std::string& dni) {
    std::ifstream archivo("doctor.csv");
    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string campoDNI;
            std::getline(ss, campoDNI, ','); // Leer el DNI (primera columna)

            if (campoDNI == dni) {
                archivo.close();
                return true; // DNI encontrado
            }
        }
        archivo.close();
    }
    else {
        std::cerr << "Error al abrir el archivo de doctores para verificar.\n";
    }
    return false; // DNI no encontrado
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
            std::cout << "Introduce el nuevo nombre (deja en blanco para mantener \"" << campoNombre << "\"): ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el búfer
            std::string entradaNombre;
            std::getline(std::cin, entradaNombre);
            if (!entradaNombre.empty()) nuevoNombre = entradaNombre;

            std::string entradaEdad;
            int nuevaEdad = std::stoi(campoEdad);
            std::cout << "Introduce la nueva edad (deja en blanco para mantener \"" << campoEdad << "\"): ";
            std::getline(std::cin, entradaEdad);
            if (!entradaEdad.empty()) nuevaEdad = std::stoi(entradaEdad);

            std::string nuevoTelefono = campoTelefono;
            std::cout << "Introduce el nuevo teléfono (deja en blanco para mantener \"" << campoTelefono << "\"): ";
            std::string entradaTelefono;
            std::getline(std::cin, entradaTelefono);
            if (!entradaTelefono.empty()) nuevoTelefono = entradaTelefono;

            std::string nuevaDireccion = campoDireccion;
            std::cout << "Introduce la nueva dirección (deja en blanco para mantener \"" << campoDireccion << "\"): ";
            std::string entradaDireccion;
            std::getline(std::cin, entradaDireccion);
            if (!entradaDireccion.empty()) nuevaDireccion = entradaDireccion;

            std::string nuevoEmail = campoEmail;
            std::cout << "Introduce el nuevo email (deja en blanco para mantener \"" << campoEmail << "\"): ";
            std::string entradaEmail;
            std::getline(std::cin, entradaEmail);
            if (!entradaEmail.empty()) nuevoEmail = entradaEmail;

            std::string nuevaEspecialidad = campoEspecialidad;
            do {
                std::cout << "Especialidad [" << campoEspecialidad << "] (Médico de familia, Pediatra, Enfermero): ";
                std::getline(std::cin, nuevaEspecialidad);

                if (nuevaEspecialidad.empty()) {
                    nuevaEspecialidad = campoEspecialidad;
                    break;
                }
                if (nuevaEspecialidad == "Médico de familia" || nuevaEspecialidad == "Pediatra" || nuevaEspecialidad == "Enfermero") {
                    break;
                }
                std::cerr << "Error: Especialidad inválida. Debe ser Médico de familia, Pediatra o Enfermero.\n";
            } while (true);

            std::string nuevaDisponibilidad = campoDisponibilidad;
            do {
                std::cout << "Disponibilidad [" << campoDisponibilidad << "] (Mañana/Tarde): ";
                std::getline(std::cin, nuevaDisponibilidad);

                if (nuevaDisponibilidad.empty()) {
                    nuevaDisponibilidad = campoDisponibilidad;
                    break;
                }
                if (nuevaDisponibilidad == "Mañana" || nuevaDisponibilidad == "Tarde") {
                    break;
                }
                std::cerr << "Error: Disponibilidad inválida. Debe ser Mañana o Tarde.\n";
            } while (true);

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
