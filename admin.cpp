#include "Admin.h"

void Admin::registrarAdmin() {
    std::cout << "Iniciando registro de administrador...\n";
    getPersonData();
    std::cout << "Introduce el rol del administrador (por defecto: Admin): ";
    std::getline(std::cin, rol);
    if (rol.empty()) rol = "Admin";

    std::ofstream archivo("admin.csv", std::ios::app);
    if (archivo.is_open()) {
        archivo << dni << "," << nombre << "," << edad << "," << telefono << "," << direccion << "," << email << "," << rol << "\n";
        archivo.close();
        std::cout << "Administrador registrado con éxito.\n";
    }
    else {
        std::cerr << "Error al abrir el archivo para guardar el administrador.\n";
    }
}

void Admin::listarAdmins() const {
    std::ifstream archivo("admin.csv");
    if (archivo.is_open()) {
        std::string linea;
        std::cout << "\n--- Lista de Administradores ---\n";
        while (std::getline(archivo, linea)) {
            std::cout << linea << std::endl;
        }
        archivo.close();
    }
    else {
        std::cerr << "Error al abrir el archivo CSV de administradores.\n";
    }
}

void Admin::eliminarAdmin(const std::string& dni) {
    std::ifstream archivo("admin.csv");
    std::ofstream temp("temp.csv");

    if (!archivo.is_open() || !temp.is_open()) {
        std::cerr << "Error al abrir los archivos para eliminar al administrador.\n";
        return;
    }

    std::string linea;
    bool encontrado = false;
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string campoDNI;
        std::getline(ss, campoDNI, ',');

        if (campoDNI == dni) {
            encontrado = true;
        }
        else {
            temp << linea << "\n";
        }
    }

    archivo.close();
    temp.close();

    if (encontrado) {
        std::remove("admin.csv");
        if (std::rename("temp.csv", "admin.csv") == 0) {
            std::cout << "Administrador con DNI " << dni << " eliminado correctamente.\n";
        }
        else {
            std::cerr << "Error al renombrar el archivo temporal.\n";
        }
    }
    else {
        std::cerr << "Administrador con DNI " << dni << " no encontrado.\n";
        std::remove("temp.csv");
    }
}

void Admin::editarAdmin(const std::string& dni) {
    std::ifstream archivo("admin.csv");
    std::ofstream temp("temp.csv");

    if (!archivo.is_open() || !temp.is_open()) {
        std::cerr << "Error al abrir los archivos para editar al administrador.\n";
        return;
    }

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string campoDNI, campoNombre, campoEdad, campoTelefono, campoDireccion, campoEmail, campoRol;

        std::getline(ss, campoDNI, ',');
        std::getline(ss, campoNombre, ',');
        std::getline(ss, campoEdad, ',');
        std::getline(ss, campoTelefono, ',');
        std::getline(ss, campoDireccion, ',');
        std::getline(ss, campoEmail, ',');
        std::getline(ss, campoRol, ',');

        if (campoDNI == dni) {
            encontrado = true;

            std::cout << "Datos actuales del administrador con DNI " << dni << ":\n";
            std::cout << "Nombre: " << campoNombre << "\n";
            std::cout << "Edad: " << campoEdad << "\n";
            std::cout << "Teléfono: " << campoTelefono << "\n";
            std::cout << "Dirección: " << campoDireccion << "\n";
            std::cout << "Email: " << campoEmail << "\n";
            std::cout << "Rol: " << campoRol << "\n";

            std::string nuevoNombre = campoNombre;
            int nuevaEdad = std::stoi(campoEdad);
            std::string nuevoTelefono = campoTelefono;
            std::string nuevaDireccion = campoDireccion;
            std::string nuevoEmail = campoEmail;
            std::string nuevoRol = campoRol;

            std::cout << "\nIntroduce los nuevos datos (deja en blanco para mantener los actuales):\n";

            std::cout << "Nombre [" << campoNombre << "]: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el búfer
            std::getline(std::cin, nuevoNombre);
            if (nuevoNombre.empty()) nuevoNombre = campoNombre;

            std::cout << "Edad [" << campoEdad << "]: ";
            std::string entradaEdad;
            std::getline(std::cin, entradaEdad);
            if (!entradaEdad.empty()) {
                try {
                    nuevaEdad = std::stoi(entradaEdad);
                    if (nuevaEdad <= 0) {
                        throw std::invalid_argument("Edad no válida");
                    }
                }
                catch (...) {
                    std::cerr << "Por favor, introduce una edad válida. Se mantiene la edad actual.\n";
                    nuevaEdad = std::stoi(campoEdad);
                }
            }
            else {
                nuevaEdad = std::stoi(campoEdad);
            }

            std::cout << "Teléfono [" << campoTelefono << "]: ";
            std::string entradaTelefono;
            std::getline(std::cin, entradaTelefono);
            if (!entradaTelefono.empty()) nuevoTelefono = entradaTelefono;

            std::cout << "Dirección [" << campoDireccion << "]: ";
            std::string entradaDireccion;
            std::getline(std::cin, entradaDireccion);
            if (!entradaDireccion.empty()) nuevaDireccion = entradaDireccion;

            std::cout << "Email [" << campoEmail << "]: ";
            std::string entradaEmail;
            std::getline(std::cin, entradaEmail);
            if (!entradaEmail.empty()) nuevoEmail = entradaEmail;

            std::cout << "Rol [" << campoRol << "]: ";
            std::string entradaRol;
            std::getline(std::cin, entradaRol);
            if (!entradaRol.empty()) nuevoRol = entradaRol;

            temp << campoDNI << "," << nuevoNombre << "," << nuevaEdad << ","
                << nuevoTelefono << "," << nuevaDireccion << "," << nuevoEmail << "," << nuevoRol << "\n";
        }
        else {
            temp << linea << "\n";
        }
    }

    archivo.close();
    temp.close();

    if (encontrado) {
        std::remove("admin.csv");
        if (std::rename("temp.csv", "admin.csv") == 0) {
            std::cout << "Datos del administrador actualizados correctamente.\n";
        }
        else {
            std::cerr << "Error al renombrar el archivo temporal.\n";
        }
    }
    else {
        std::cerr << "Administrador con DNI " << dni << " no encontrado.\n";
        std::remove("temp.csv");
    }
}

