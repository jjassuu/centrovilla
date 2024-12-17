#ifndef usuarios_h
#define usuarios_h

#include <unordered_map>
#include <string>

// Declaración de funciones
void cargarusuario(std::unordered_map<std::string, std::string>& users);
void guardarusuario(const std::unordered_map<std::string, std::string>& users);
bool login(const std::unordered_map<std::string, std::string>& users);
void registrar(std::unordered_map<std::string, std::string>& users);

#endif
