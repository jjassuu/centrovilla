#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <algorithm> // Para std::transform
#include <cctype>    // Para std::toupper

static std::string convertirAMayusculas(const std::string& cadena) {
    std::string resultado = cadena;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return resultado;
}

class Person {
protected:
    std::string dni;
    int edad = 0;
    std::string nombre;
    std::string telefono;
    std::string direccion;
    std::string email;

public:
    Person(const std::string& dni = "", const std::string& nombre = "", int edad = 0,
        const std::string& telefono = "", const std::string& direccion = "",
        const std::string& email = "")
        : dni(dni), nombre(nombre), edad(edad), telefono(telefono), direccion(direccion), email(email) {}

    void getPersonData();
    void showPersonData() const;

    static bool validarDNI(const std::string& dni);
    static bool validarEdad(int edad);
    static bool validarEmail(const std::string& email);
    static bool validarTelefono(const std::string& telefono);
};

#endif
