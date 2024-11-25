// centrovilla.cpp: define el punto de entrada de la aplicación.
//

#include "centrovilla.h"
#include <iostream>
#include <fstream>
#include <unordered_map>


// Función para cargar usuarios desde un archivo
void cargarusuario(std::unordered_map<std::string, std::string>& users) {
    std::ifstream file("users.txt");
    if (file.is_open()) {
        std::string username, password;
        while (file >> username >> password) {
            users[username] = password;
        }
        file.close();
    }
}

// Función para guardar usuarios en un archivo
void guardarusuario(const std::unordered_map<std::string, std::string>& users) {
    std::ofstream file("users.txt", std::ios::trunc);
    if (file.is_open()) {
        for (const auto& pair : users) {
            file << pair.first << " " << pair.second << "\n";
        }
        file.close();
    }
}

// Función para realizar el inicio de sesión
bool login(const std::unordered_map<std::string, std::string>& users) {
    std::string username, password;
    std::cout << "=== INICIO DE SESION ===\n";
    std::cout << "Usuario: ";
    std::cin >> username;
    std::cout << "Contrasena: ";
    std::cin >> password;

    if (users.find(username) != users.end() && users.at(username) == password) {
        std::cout << "Inicio de sesion exitoso. Bienvenido, " << username << "!\n";
        return true;
    }
    else {
        std::cout << "Usuario o contrasena incorrectos.\n";
        return false;
    }
}

// Función para registrar un nuevo usuario
void registrar(std::unordered_map<std::string, std::string>& users) {
    std::string username, password;
    std::cout << "=== REGISTRAR NUEVO USUARIO ===\n";
    std::cout << "Usuario: ";
    std::cin >> username;

    if (users.find(username) != users.end()) {
        std::cout << "El usuario ya existe.\n";
        return;
    }

    std::cout << "Contrasena: ";
    std::cin >> password;
    users[username] = password;
    guardarusuario(users);
    std::cout << "Usuario registrado con exito.\n";
}

// Función para mostrar el menú principal
void mainMenu() {
    std::cout << "\n=== Centro de Salud Villa ===\n";
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
