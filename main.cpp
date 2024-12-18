#include "usuarios.h"
#include "doctor.h"
#include "paciente.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

// Función para mostrar el menú principal
void mainMenu() {
    int option;
    do {
        std::cout << "\n=== Centro de Salud Villa ===\n";
        std::cout << "1. Gestionar Doctores\n";
        std::cout << "2. Gestionar Pacientes\n";
        std::cout << "3. Gestionar Citas\n";
        std::cout << "4. Cerrar sesión\n";
        std::cout << "Elige una opción: ";
        std::cin >> option;

        switch (option) {
        case 1:
        {
            int doctorOption;
            cout << "\n1. Añadir Doctor\n2. Ver Todos los Doctores\nElige una opción: ";
            cin >> doctorOption;
            if (doctorOption == 1) {
                Doctor newDoctor;
                newDoctor.añadirDoctor();
            }
            else if (doctorOption == 2) {
                Doctor::mostrarDoctor();
            }
            else {
                cout << "Opción inválida.\n";
            }
            break;
        }
        case 2:
        {
            int opcionpaciente;
            std::cout << "\n1. Añadir Paciente\n2. Ver Todos los Pacientes\nElige una opción: ";
            std::cin >> opcionpaciente;
            if (opcionpaciente == 1) {
                Paciente newPatient;
                newPatient.añadirpaciente();
            }
            else if (opcionpaciente == 2) {
                Paciente::mostarpacientes();
            }
            else {
                std::cout << "Opción inválida.\n";
            }
            break;
        }
            break;
        case 3:
            std::cout << ".\n";
            break;
        case 4:
            std::cout << "Cerrando sesión...\n";
            return; 
        default:
            std::cout << "Opción inválida. Inténtalo de nuevo.\n";
            break;
        }
    } while (option != 4);
}

int main() {
    std::unordered_map<std::string, std::string> users;
    cargarusuario(users);

    int option;
    bool loggedIn = false; // Para controlar la sesión

    do {
        std::cout << "\n=== Bienvenido al Centro de Salud Villa ===\n";
        std::cout << "1. Iniciar sesión\n";
        std::cout << "2. Registrar usuario\n";
        std::cout << "3. Salir\n";
        std::cout << "Elige una opción: ";
        std::cin >> option;

        switch (option) {
        case 1:
            if (login(users)) {
                loggedIn = true;
                mainMenu(); // Acceder al menú principal
                loggedIn = false; // Una vez finalizado, volver a inicio
            }
            break;
        case 2:
            registrar(users);
            break;
        case 3:
            std::cout << "Saliendo del sistema...\n";
            break;
        default:
            std::cout << "Opción inválida. Inténtalo de nuevo.\n";
            break;
        }
    } while (option != 3 && !loggedIn); // Detener el bucle correctamente

    return 0;
}
