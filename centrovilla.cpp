#include "usuarios.h"
#include "centrovilla.h"
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
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el búfer de entrada
        std::cin >> option;

        switch (option) {
        case 1:
            
            break;
        case 2:
           
            break;
        case 3:
            
            break;
        case 4:
            std::cout << "Cerrando sesión...\n";
            break;
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
    do {
        std::cout << "\n=== Bienvenido al centro de salud villa===\n";
        std::cout << "1. Iniciar sesión\n";
        std::cout << "2. Registrar usuario\n";
        std::cout << "3. Salir\n";
        std::cout << "Elige una opción: ";
        std::cin >> option;

        switch (option) {
        case 1:
            if (login(users)) {
                mainMenu();
            }
            break;
        case 2:
            registrar(users);
            break;
        case 3:
            std::cout << "Saliendo del sistema...\n";
            break;
        default:
            std::cout << "Opción inválida. Intentalo de nuevo.\n";
            break;
        }
    } while (option != 3);

    return 0;
}
