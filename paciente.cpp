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
    // Validar que el DNI no est� vac�o
    if (dni.empty()) {
        std::cerr << "Error: El DNI no puede estar vac�o.\n";
        return;
    }

    // Validar el formato del DNI
    if (!Person::validarDNI(dni)) {
        std::cerr << "Error: El DNI ingresado no tiene un formato v�lido. Debe contener 8 n�meros seguidos de una letra.\n";
        return;
    }

    // Validar que el paciente exista
    if (!Paciente::existePaciente(dni)) {
        std::cerr << "Error: El paciente con DNI " << dni << " no est� registrado.\n";
        return;
    }

    // Validar que la fecha no est� vac�a y tenga el formato correcto
    if (fecha.empty()) {
        std::cerr << "Error: La fecha no puede estar vac�a.\n";
        return;
    }

    if (!GestionCitas::validarFecha(fecha)) {
        std::cerr << "Error: La fecha no tiene un formato v�lido. Ejemplo: 2025-01-19.\n";
        return;
    }

    // Validar que la descripci�n no est� vac�a
    if (descripcion.empty()) {
        std::cerr << "Error: La descripci�n no puede estar vac�a.\n";
        return;
    }

    // Validar que el nombre del m�dico no est� vac�o
    if (medico.empty()) {
        std::cerr << "Error: El nombre del m�dico no puede estar vac�o.\n";
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
        getPersonData(); // Solicita y valida todos los datos b�sicos del paciente.

        // Guardar en archivo
        guardarEnArchivo();
        std::cout << "\nPaciente registrado con �xito.\n";
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
  

// Eliminar paciente
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

    if (archivo.is_open() && temp.is_open()) {
        std::string linea;
        bool encontrado = false;

        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            std::string campoDNI, campoNombre, campoEdad, campoTelefono, campoDireccion, campoEmail;

            // Leer cada campo de la linea
            std::getline(ss, campoDNI, ',');
            std::getline(ss, campoNombre, ',');
            std::getline(ss, campoEdad, ',');
            std::getline(ss, campoTelefono, ',');
            std::getline(ss, campoDireccion, ',');
            std::getline(ss, campoEmail, ',');
            
            if (campoDNI == dni) {
                encontrado = true;

                std::cout << "Datos actuales del paciente con DNI " << dni << ":\n";
                std::cout << "Nombre: " << campoNombre << "\n";
                std::cout << "Edad: " << campoEdad << "\n";
                std::cout << "Telefono: " << campoTelefono << "\n";
                std::cout << "Direccion: " << campoDireccion << "\n";
                std::cout << "Email: " << campoEmail << "\n";

                std::string nuevoNombre, nuevoTelefono, nuevaDireccion, nuevoEmail;
                int nuevaEdad;

                temp << campoDNI << "," << nombre << "," << edad << ","
                    << telefono << "," << direccion << ","
                    << email << "," << "\n";
                std::cout << "Datos del paciente actualizados correctamente.\n";
            }
            else {
                // Copiar la linea tal como esta si no es el paciente a editar
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
    else {
        std::cerr << "Error al abrir los archivos para editar al paciente.\n";
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
