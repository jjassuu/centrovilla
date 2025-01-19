#include "usuarios.h"

// Funcion para cargar usuarios desde un archivo
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

// Funcion para guardar usuarios en un archivo
void guardarusuario(const std::unordered_map<std::string, std::string>& users) {
    std::ofstream file("users.txt", std::ios::trunc);
    if (file.is_open()) {
        for (const auto& pair : users) {
            file << pair.first << " " << pair.second << "\n";
        }
        file.close();
    }
}

// Funcion para realizar el inicio de sesion
bool login(const std::unordered_map<std::string, std::string>& users) {
    std::string username, password;
    std::cout << "=== INICIO DE SESION ===\n";
    std::cout << "Usuario: ";
    std::cin >> username;
    std::cout << "Contrasena: ";
    std::cin >> password;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el bufer

    if (users.find(username) != users.end() && users.at(username) == password) {
        std::cout << "Inicio de sesion exitoso. Bienvenido, " << username << "!\n";
        return true;
    }
    else {
        std::cout << "Usuario o contrasena incorrectos.\n";
        return false;
    }
}


// Funcion para registrar un nuevo usuario
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
