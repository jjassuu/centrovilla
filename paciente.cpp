#include "paciente.h"
#include <iomanip>
#include <regex>
Paciente::Paciente(const std::string& dni, const std::string& nombre, int edad,
    const std::string& telefono, const std::string& direccion,
    const std::string& email)
    : Person(dni, nombre, edad, telefono, direccion, email){}

bool Paciente::existePaciente(const std::string& dni) {
    if (!Person::validarDNI(dni)) { 
        return false;
    }

    std::ifstream archivo("pacientes.csv");
    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string campoDNI;
            std::getline(ss, campoDNI, ','); // Leer el DNI (primera columna)

            if (convertirAMayusculas(campoDNI) == convertirAMayusculas(dni)) {
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

// Agregar una dolencia al historial
void Paciente::agregarDolencia(const std::string& dni, const std::string& fecha, const std::string& descripcion, const std::string& medico) {
    // Validar que el DNI no esté vacío
    if (dni.empty()) {
        std::cerr << "Error: El DNI no puede estar vacío.\n";
        return;
    }

    // Validar el formato del DNI
    if (!Person::validarDNI(dni)) {
        std::cerr << "Error: El DNI ingresado no tiene un formato válido. Debe contener 8 números seguidos de una letra.\n";
        return;
    }

    // Validar que el paciente exista
    if (!Paciente::existePaciente(dni)) {
        std::cerr << "Error: El paciente con DNI " << dni << " no está registrado.\n";
        return;
    }

    // Validar que la fecha no esté vacía y tenga el formato correcto
    if (fecha.empty()) {
        std::cerr << "Error: La fecha no puede estar vacía.\n";
        return;
    }

    if (!GestionCitas::validarFecha(fecha)) {
        std::cerr << "Error: La fecha no tiene un formato válido. Ejemplo: 2025-01-19.\n";
        return;
    }

    // Validar que la descripción no esté vacía
    if (descripcion.empty()) {
        std::cerr << "Error: La descripción no puede estar vacía.\n";
        return;
    }

    // Validar que el nombre del médico no esté vacío
    if (medico.empty()) {
        std::cerr << "Error: El nombre del médico no puede estar vacío.\n";
        return;
    }
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
                    << ", Descripcion: " << descripcion
                    << ", Medico: " << medico << "\n";
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
    try {
        getPersonData(); // Solicita y valida todos los datos básicos del paciente.

        // Guardar en archivo
        guardarEnArchivo();
        std::cout << "\nPaciente registrado con éxito.\n";
    }
    catch (const std::runtime_error& e) {
        std::cerr << "\nRegistro cancelado: " << e.what() << "\n";
    }
}


// Guardar paciente en el archivo.
void Paciente::guardarEnArchivo() const {
    std::ofstream archivo("pacientes.csv", std::ios::app);
    if (archivo.is_open()) {
        archivo<< dni << "," << nombre << "," << edad << "," << telefono << "," << direccion << "," << email << "," << ","  << "\n";
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

void Paciente::buscarPaciente(const std::string& dni) {

    std::ifstream archivo("pacientes.csv");
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo 'pacientes.csv'. Verifica que el archivo exista y tenga los permisos necesarios.\n";
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string campoDNI;
        std::getline(ss, campoDNI, ',');

        if (convertirAMayusculas(campoDNI) == convertirAMayusculas(dni)) {
            std::cout << "Paciente encontrado: " << linea << "\n";
            archivo.close();
            return;
        }
    }

    std::cout << "Paciente con DNI " << dni << " no encontrado.\n";
    archivo.close();
}
  


void Paciente::eliminarPaciente(const std::string& dni) {
    std::ifstream archivo("pacientes.csv");
    std::ofstream temp("temp.csv");

    if (archivo.is_open() && temp.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string campo;
            std::getline(ss, campo, ','); 

           
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

    if (!archivo.is_open() || !temp.is_open()) {
        std::cerr << "Error al abrir los archivos para editar al paciente.\n";
        return;
    }

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string campoDNI, campoNombre, campoEdad, campoTelefono, campoDireccion, campoEmail;

        std::getline(ss, campoDNI, ',');
        std::getline(ss, campoNombre, ',');
        std::getline(ss, campoEdad, ',');
        std::getline(ss, campoTelefono, ',');
        std::getline(ss, campoDireccion, ',');
        std::getline(ss, campoEmail, ',');

        if (convertirAMayusculas(campoDNI) == convertirAMayusculas(dni)) {
            encontrado = true;

            std::cout << "Datos actuales del paciente con DNI " << dni << ":\n";
            std::cout << "Nombre: " << campoNombre << "\n";
            std::cout << "Edad: " << campoEdad << "\n";
            std::cout << "Teléfono: " << campoTelefono << "\n";
            std::cout << "Dirección: " << campoDireccion << "\n";
            std::cout << "Email: " << campoEmail << "\n";

            std::string nuevoNombre = campoNombre, nuevoTelefono = campoTelefono, nuevaDireccion = campoDireccion, nuevoEmail = campoEmail;
            int nuevaEdad = std::stoi(campoEdad);

            std::cout << "Introduce el nuevo nombre (deja en blanco para mantener \"" << campoNombre << "\"): ";
            std::string entradaNombre;
            std::getline(std::cin, entradaNombre);
            if (!entradaNombre.empty()) nuevoNombre = entradaNombre;

            do {
                std::cout << "Introduce la nueva edad (deja en blanco para mantener \"" << campoEdad << "\"): ";
                std::string entradaEdad;
                std::getline(std::cin, entradaEdad);
                if (entradaEdad.empty()) break; 
                try {
                    int edadTemp = std::stoi(entradaEdad);
                    if (Person::validarEdad(edadTemp)) {
                        nuevaEdad = edadTemp;
                        break;
                    }
                }
                catch (...) {
                    std::cerr << "Por favor, introduce una edad válida.\n";
                }
            } while (true);

            std::cout << "Introduce el nuevo número de teléfono (deja en blanco para mantener \"" << campoTelefono << "\"): ";
            std::string entradaTelefono;
            std::getline(std::cin, entradaTelefono);
            if (!entradaTelefono.empty()) {
                if (Person::validarTelefono(entradaTelefono)) {
                    nuevoTelefono = entradaTelefono;
                }
                else {
                    std::cerr << "Error: El teléfono debe contener exactamente 9 dígitos.\n";
                    std::cerr << "Número de teléfono inválido. Se mantendrá el valor actual.\n";
                }
            }

            std::cout << "Introduce la nueva dirección (deja en blanco para mantener \"" << campoDireccion << "\"): ";
            std::string entradaDireccion;
            std::getline(std::cin, entradaDireccion);
            if (!entradaDireccion.empty()) nuevaDireccion = entradaDireccion;

            std::cout << "Introduce el nuevo email (deja en blanco para mantener \"" << campoEmail << "\"): ";
            std::string entradaEmail;
            std::getline(std::cin, entradaEmail);
            if (!entradaEmail.empty()) {
                if (Person::validarEmail(entradaEmail)) {
                    nuevoEmail = entradaEmail;
                }
                else {
                    std::cerr << "Error: El email no tiene un formato válido.\n";
                    std::cerr << "Email inválido. Se mantendrá el valor actual.\n";
                }
            }
 
            temp << campoDNI << "," << nuevoNombre << "," << nuevaEdad << ","
                << nuevoTelefono << "," << nuevaDireccion << "," << nuevoEmail << "\n";
            std::cout << "Datos del paciente actualizados correctamente.\n";
        }
        else {
            temp << linea << "\n";
        }
    }

    archivo.close();
    temp.close();

    if (encontrado) {
        std::remove("pacientes.csv");
        std::rename("temp.csv", "pacientes.csv");
    }
    else {
        std::cout << "Paciente con DNI " << dni << " no encontrado.\n";
        std::remove("temp.csv");
    }
}

std::string Paciente::derivarPaciente(const std::string& centro) {
    const int longitudCodigo = 25;
    static const char caracteres[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    static const int numCaracteres = sizeof(caracteres) - 1;

    std::string codigo;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, numCaracteres - 1);

    for (int i = 0; i < longitudCodigo; ++i) {
        codigo += caracteres[distrib(gen)];
    }

    std::ofstream archivo("derivaciones.csv", std::ios::app);
    if (archivo.is_open()) {
        archivo << dni << "," << centro << "," << codigo << "\n";
        archivo.close();
        std::cout << "Paciente derivado al centro \"" << centro << "\" con el codigo: " << codigo << "\n";
    }
    else {
        std::cerr << "Error al guardar la derivacion.\n";
    }

    return codigo;
}
