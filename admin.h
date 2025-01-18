#ifndef ADMIN_H
#define ADMIN_H

#include "person.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Admin : public Person {
private:
    std::string rol;

public:
    Admin(const std::string& dni = "", const std::string& nombre = "", int edad = 0,
        const std::string& telefono = "", const std::string& direccion = "",
        const std::string& email = "", const std::string& rol = "Admin")
        : Person(dni, nombre, edad, telefono, direccion, email), rol(rol) {}

    void registrarAdmin();
    void listarAdmins() const;
    static void eliminarAdmin(const std::string& dni);
    static void editarAdmin(const std::string& dni);
};

#endif