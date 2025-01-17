#include "paciente.h"
#include <iomanip>
#include <regex>

bool validarEdad(int edad) {
    if (edad <= 0) {
        std::cerr << "Error: La edad debe ser un número positivo.\n";
        return false;
    }
    return true;
}


bool validarEmail(const std::string& email) {
    std::regex patronEmail(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!std::regex_match(email, patronEmail)) {
        std::cerr << "Error: El email no tiene un formato válido.\n";
        return false;
    }
    return true;
}


bool validarTelefono(const std::string& telefono) {
    std::regex patronTelefono(R"(^\d{9}$)");
    if (!std::regex_match(telefono, patronTelefono)) {
        std::cerr << "Error: El teléfono debe contener 9 dígitos.\n";
        return false;
    }
    return true;
}

bool Paciente::existePaciente(const std::string& dni) {
    std::ifstream archivo("pacientes.csv");
    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string campoDNI;
            std::getline(ss, campoDNI, ','); // Leer el DNI (primera columna)

            if (campoDNI == dni) {
                archivo.close();
                return true; // DNI encontrado, existe duplicado
            }
        }
        archivo.close();
    }
    else {
        std::cerr << "Error al abrir el archivo de pacientes para verificar duplicados.\n";
    }
    return false; // DNI no encontrado
}

bool Paciente::validarDNI(const std::string& dni) {
    // Expresión regular para 8 dígitos seguidos de 1 letra
    std::regex formatoDNI("^\\d{8}[A-Za-z]$");

    if (!std::regex_match(dni, formatoDNI)) {
        std::cerr << "Error: El DNI debe tener 8 números seguidos de 1 letra.\n";
        return false;
    }
    return true;
}
// Constructor de la clase Paciente
Paciente::Paciente(const std::string& dni, const std::string& nombre, int edad,
    const std::string& telefono, const std::string& direccion,
    const std::string& email, const std::string& fechaCita)
    : dni(dni), nombre(nombre), edad(edad), telefono(telefono), direccion(direccion),
    email(email), diacita(fechaCita) {}

// Agregar una dolencia al historial
void Paciente::agregarDolencia(const std::string& dni, const std::string& fecha, const std::string& descripcion, const std::string& medico) {
    std::ofstream archivo("historial_dolencias.csv", std::ios::app);
    if (archivo.is_open()) {
        archivo << dni << "," << fecha << "," << descripcion << "," << medico << "\n";
        archivo.close();
        std::cout << "Dolencia registrada correctamente.\n";
    }
    else {
        std::cerr << "Error al abrir el archivo para registrar la dolencia.\n";
    }
}


// Mostrar el historial de dolencias
void Paciente::mostrarHistorialDolencias (const std::string& dni)  {
    std::ifstream archivo("historial_dolencias.csv");
    if (archivo.is_open()) {
        std::string linea;
        bool encontrado = false;
        std::cout << "Historial de dolencias para el paciente con DNI " << dni << ":\n";
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string campoDNI, fecha, descripcion, medico;
            std::getline(ss, campoDNI, ',');
            std::getline(ss, fecha, ',');
            std::getline(ss, descripcion, ',');
            std::getline(ss, medico, ',');

            if (campoDNI == dni) {
                encontrado = true;
                std::cout << "- Fecha: " << fecha
                    << ", Descripción: " << descripcion
                    << ", Médico: " << medico << "\n";
            }
        }
        if (!encontrado) {
            std::cout << "No se encontraron dolencias para este paciente.\n";
        }
        archivo.close();
    }
    else {
        std::cerr << "Error al abrir el archivo del historial de dolencias.\n";
    }
}

// Registrar un nuevo paciente.
void Paciente::registrarPaciente() {
    do{
        std::cout << "Introduce el DNI del paciente\n";
        std::cin >> dni;
        std::cin.ignore();

        if (!validarDNI(dni)) {
            std::cout << "Por favor, introduce un DNI válido.\n";
        }
        else if(existePaciente(dni)){
            std::cerr << "Error: El paciente con DNI " << dni << " ya está registrado.\n";
            return;
        }
        else {
            break;
        }
    } while (true);

    std::cout << "Introduce el nombre: ";
    std::getline(std::cin, nombre);

    do{
        std::cout << "Introduce la edad: ";
        std::cin >> edad;
        if (!validarEdad(edad)) {
            std::cerr << "Por favor, introduce una edad válida (mayor que 0).\n";
        }
        else {
            break;
        }
    
    } while (true);
    std::cin.ignore();
    
    do{
        std::cout << "Introduce el teléfono: ";
        std::getline(std::cin, telefono);
        if (!validarTelefono(telefono)) {
            std::cerr << "Por favor, introduce un teléfono válido.\n";
        }
        else {
            break;
        }
    } while (true);

    std::cout << "Introduce la dirección: ";
    std::getline(std::cin, direccion);

    do{
        std::cout << "Introduce el correo electrónico: ";
        std::getline(std::cin, email);
        if (!validarEmail(email)) {
            std::cerr << "Por favor, introduce un email válido.\n";
        }
        else {
            break;
        }
    } while (true);
    std::cout << "Introduce la fecha de la cita (YYYY-MM-DD): ";
    std::cin >> diacita;

    guardarEnArchivo();
    std::cout << "\nPaciente registrado con éxito.\n";
}

// Guardar paciente en el archivo.
void Paciente::guardarEnArchivo() const {
    std::ofstream archivo("pacientes.csv", std::ios::app);
    if (archivo.is_open()) {
        archivo<< dni << "," << nombre << "," << edad << "," << telefono << "," << direccion << "," << email << "," << "," << diacita << "\n";
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
void Paciente::eliminarPaciente(const std::string& dni) {
    std::ifstream archivo("pacientes.csv");
    std::ofstream temp("temp.csv");

    if (archivo.is_open() && temp.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string campo;
            std::getline(ss, campo, ','); // Leer el DNI

           
            if (campo !=dni) {
                temp << linea << "\n";
            }
        }
        archivo.close();
        temp.close();
        
        if (std::remove("pacientes.csv") != 0) {
            std::cerr << "Error al eliminar el archivo original 'pacientes.csv'.\n";
            return;
        }

        if (std::rename("temp.csv", "pacientes.csv") != 0) {
            std::cerr << "Error al renombrar el archivo temporal.\n";
            return;
        }
        
        std::cout << "Paciente con ID " << dni << " eliminado correctamente.\n";
    } 
    else {
            std::cerr << "Error al abrir los archivos para eliminar al paciente.\n";
        }
}

void Paciente::editarPaciente(const std::string& dni) {
    std::ifstream archivo("pacientes.csv");
    std::ofstream temp("temp.csv");

    if (archivo.is_open() && temp.is_open()) {
        std::string linea;
        bool encontrado = false;

        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string campoDNI, campoNombre, campoEdad, campoTelefono, campoDireccion, campoEmail, campoFechaCita;

            // Leer cada campo de la línea
            std::getline(ss, campoDNI, ',');
            std::getline(ss, campoNombre, ',');
            std::getline(ss, campoEdad, ',');
            std::getline(ss, campoTelefono, ',');
            std::getline(ss, campoDireccion, ',');
            std::getline(ss, campoEmail, ',');
            std::getline(ss, campoFechaCita, ',');

            if (campoDNI == dni) {
                encontrado = true;

                // Mostrar los datos actuales
                std::cout << "Datos actuales del paciente con DNI " << dni << ":\n";
                std::cout << "Nombre: " << campoNombre << "\n";
                std::cout << "Edad: " << campoEdad << "\n";
                std::cout << "Teléfono: " << campoTelefono << "\n";
                std::cout << "Dirección: " << campoDireccion << "\n";
                std::cout << "Email: " << campoEmail << "\n";
                std::cout << "Fecha de la cita: " << campoFechaCita << "\n";

                // Pedir nuevos datos con validación
                std::string nuevoNombre = campoNombre;
                int nuevaEdad = 0;
                try {
                    nuevaEdad = std::stoi(campoEdad);
                }
                catch (...) {
                    nuevaEdad = 0; // Si no es válido, asignar un valor predeterminado
                }
                std::string nuevoTelefono = campoTelefono;
                std::string nuevaDireccion = campoDireccion;
                std::string nuevoEmail = campoEmail;
                std::string nuevaFechaCita = campoFechaCita;

                std::cout << "\nIntroduce los nuevos datos (deja en blanco para mantener los actuales):\n";

                // Nombre
                std::cout << "Nombre [" << campoNombre << "]: ";
                std::getline(std::cin, nuevoNombre);
                if (nuevoNombre.empty()) {
                    nuevoNombre = campoNombre;
                }

                // Edad
                do {
                    std::cout << "Edad [" << campoEdad << "]: ";
                    std::string entradaEdad;
                    std::getline(std::cin, entradaEdad);
                    if (entradaEdad.empty()) {
                        break; // Mantener la edad actual
                    }
                    try {
                        nuevaEdad = std::stoi(entradaEdad);
                        if (validarEdad(nuevaEdad)) {
                            break;
                        }
                    }
                    catch (...) {
                        std::cerr << "Por favor, introduce una edad válida.\n";
                    }
                } while (true);

                // Teléfono
                do {
                    std::cout << "Teléfono [" << campoTelefono << "]: ";
                    std::getline(std::cin, nuevoTelefono);
                    if (nuevoTelefono.empty()) {
                        nuevoTelefono = campoTelefono;
                        break;
                    }
                    if (validarTelefono(nuevoTelefono)) {
                        break;
                    }
                } while (true);

                // Dirección
                std::cout << "Dirección [" << campoDireccion << "]: ";
                std::getline(std::cin, nuevaDireccion);
                if (nuevaDireccion.empty()) {
                    nuevaDireccion = campoDireccion;
                }

                // Email
                do {
                    std::cout << "Email [" << campoEmail << "]: ";
                    std::getline(std::cin, nuevoEmail);
                    if (nuevoEmail.empty()) {
                        nuevoEmail = campoEmail;
                        break;
                    }
                    if (validarEmail(nuevoEmail)) {
                        break;
                    }
                } while (true);

                // Fecha de cita
                std::cout << "Fecha de la cita [" << campoFechaCita << "]: ";
                std::getline(std::cin, nuevaFechaCita);
                if (nuevaFechaCita.empty()) {
                    nuevaFechaCita = campoFechaCita;
                }

                // Escribir los nuevos datos en el archivo temporal
                temp << campoDNI << "," << nuevoNombre << "," << nuevaEdad << ","
                    << nuevoTelefono << "," << nuevaDireccion << ","
                    << nuevoEmail << "," << nuevaFechaCita << "\n";
                std::cout << "Datos del paciente actualizados correctamente.\n";
            }
            else {
                // Copiar la línea tal como está si no es el paciente a editar
                temp << linea << "\n";
            }
        }

        archivo.close();
        temp.close();

        if (encontrado) {
            // Sustituir el archivo original por el temporal
            if (std::remove("pacientes.csv") != 0) {
                std::cerr << "Error al eliminar el archivo original 'pacientes.csv'.\n";
                return;
            }

            if (std::rename("temp.csv", "pacientes.csv") != 0) {
                std::cerr << "Error al renombrar el archivo temporal.\n";
                return;
            }
        }
        else {
            std::cout << "Paciente con DNI " << dni << " no encontrado.\n";
            std::remove("temp.csv"); // Eliminar el archivo temporal si no se encontró el paciente
        }
    }
    else {
        std::cerr << "Error al abrir los archivos para editar al paciente.\n";
    }
}
