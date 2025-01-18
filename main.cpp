﻿#include "usuarios.h"
#include "doctor.h"
#include "admin.h"
#include "person.h"
#include "paciente.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "cita.h"
#include <limits>


void mainMenu() {
    int option;
    do {
        std::cout << "\n=== Centro de Salud Villa ===\n";
        std::cout << "1. Gestionar Doctores\n";
        std::cout << "2. Gestionar Pacientes\n";
        std::cout << "3. Gestionar Citas\n";
        std::cout << "4. Gestionar Administradores\n";
        std::cout << "5. Cerrar sesión\n";
        std::cout << "Elige una opción: ";

        if (!obtenerEntrada(option)) {
            std::cout << "Entrada inválida. Por favor, introduce un número.\n";
            continue; // Vuelve al menú principal
        }

        switch (option) {
        case 1:
        {
            int doctorOption;
            std::cout << "\n1. Añadir Doctor\n";
            std::cout << "2. Ver Todos los Doctores\n";
            std::cout << "3. Eliminar Doctor\n";
            std::cout << "4. Editar Doctor\n";
            std::cout << "Elige una opción: ";
            if (!obtenerEntrada(doctorOption)) {
                std::cout << "Entrada inválida. Por favor, introduce un número.\n";
                break; // Regresa al menú principal
            }
            if (doctorOption == 1) {
                Doctor nuevoDoctor;
                nuevoDoctor.registrarDoctor();
            }
            else if (doctorOption == 2) {
                Doctor::listarDoctores();
            }
            else if (doctorOption == 3) { 
                std::string dni;
                std::cout << "Introduce el DNI del doctor que deseas eliminar: ";
                std::cin >> dni;
                Doctor::eliminarDoctor(dni); 
            }
            else if (doctorOption == 4) { 
                std::string dni;
                std::cout << "Introduce el DNI del doctor que deseas editar: ";
                std::cin >> dni;
                Doctor::editarDoctor(dni);
            }
            else {
                cout << "Opción inválida.\n";
            }
            break;
        }
        case 2:
        {
            int opcionpaciente;
            std::cout << "\n1. Añadir Paciente\n";
            std::cout << "2. Ver Todos los Pacientes\n";
            std::cout << "3. Buscar paciente por DNI\n";
            std::cout << "4. Agregar Dolencia\n";
            std::cout << "5. Mostrar Historial de Dolencias\n";
            std::cout << "6. Editar paciente\n";
            std::cout << "7. Eliminar paciente\n";
            std::cout << "Elige una opcion\n";
            if (!obtenerEntrada(opcionpaciente)) {
                std::cout << "Entrada inválida. Por favor, introduce un número.\n";
                break; // Regresa al menú principal
            }

            if (opcionpaciente == 1) {
                Paciente nuevoPaciente;
                nuevoPaciente.registrarPaciente();
            }
            else if (opcionpaciente == 2) {
                Paciente::listarPacientes();
            }
            else if (opcionpaciente == 3) {
                std::string dni;
                std::cout << "Introduce el DNI del paciente a buscar: ";
                std::cin >> dni;
                Paciente::buscarPaciente(dni);
            }
            else if (opcionpaciente == 4) {
                // Agreg dolencia a un paciente
                std::string dni, fecha, descripcion, medico;
                std::cout << "Introduce el DNI del paciente: ";
                std::cin >> dni;
                std::cin.ignore();
                std::cout << "Introduce la fecha (YYYY-MM-DD): ";
                std::getline(std::cin, fecha);
                std::cout << "Introduce la descripción de la dolencia: ";
                std::getline(std::cin, descripcion);
                std::cout << "Introduce el nombre del médico: ";
                std::getline(std::cin, medico);

              
                Paciente paciente;
                paciente.agregarDolencia(dni, fecha, descripcion, medico);
            }
            else if (opcionpaciente == 5) {
                // Mostrar historial de dolencias
                std::string dni;
                std::cout << "Introduce el DNI del paciente: ";
                std::cin >> dni;
           
                Paciente paciente;
                paciente.mostrarHistorialDolencias(dni);
            }
            else if (opcionpaciente == 6) {
                std::string dni;
                std::cout << "Introduce el DNI del paciente a editar: ";
                std::cin >> dni;
                std::cin.ignore();
                Paciente paciente;
                paciente.editarPaciente(dni);
            }
            else if (opcionpaciente == 7) {
                std::string dni;
                std::cout << "Introduce el DNI del paciente a eliminar: ";
                std::cin >> dni;
                
                Paciente::eliminarPaciente(dni);
            }
            else {
                std::cout << "Opción inválida.\n";
            }
            break;
        }
            break;
        case 3: {
            int citaOpcion;
            std::cout << "\n1. Agendar Cita\n2. Ver Todas las Citas\nElige una opción: ";
            std::cin >> citaOpcion;

            if (!obtenerEntrada(citaOpcion)) {
                std::cout << "Entrada inválida. Por favor, introduce un número.\n";
                break; // Regresa al menú principal
            }

            if (citaOpcion == 1) {
                int pacienteID, doctorID;
                std::string fecha, hora;
                std::cout << "Introduce el DNI del Paciente: ";
                std::cin >> pacienteID;
                std::cout << "Introduce el DNI del Doctor: ";
                std::cin >> doctorID;
                std::cout << "Introduce la Fecha (DD:MM:YYYY): ";
                std::cin >> fecha;
                std::cout << "Introduce la Hora (HH:MM): ";
                std::cin >> hora;

                Cita nuevaCita;
                nuevaCita.programarcita(pacienteID, doctorID, fecha, hora);
            }
            else if (citaOpcion == 2) {
                Cita::mostrarcitas();
            }
            else {
                std::cout << "Opción inválida.\n";
            }
            break;
        }case 4: {
            int adminOpcion;
            std::cout << "\n1. Añadir Administrador\n";
            std::cout << "2. Ver Todos los Administradores\n";
            std::cout << "3. Eliminar Administrador\n";
            std::cout << "4. Editar Administrador\n";
            std::cout << "Elige una opción: ";
            if (!obtenerEntrada(adminOpcion)) {
                std::cout << "Entrada inválida. Por favor, introduce un número.\n";
                break; // Regresa al menú principal
            }

            if (adminOpcion == 1) {
                Admin nuevoAdmin;
                nuevoAdmin.registrarAdmin();
            }
            else if (adminOpcion == 2) {
                Admin().listarAdmins();
            }
            else if (adminOpcion == 3) {
                std::string dni;
                std::cout << "Introduce el DNI del administrador que deseas eliminar: ";
                std::cin >> dni;
                Admin::eliminarAdmin(dni);
            }
            else if (adminOpcion == 4) {
                std::string dni;
                std::cout << "Introduce el DNI del administrador que deseas editar: ";
                std::cin >> dni;
                Admin::editarAdmin(dni);
            }
            else {
                std::cout << "Opción inválida.\n";
            }
            break;
        }
        case 5:
            std::cout << "Cerrando sesión...\n";
            return; 
        default:
            std::cout << "Opción inválida. Inténtalo de nuevo.\n";
            break;
        }
    } while (option != 5);
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

        if (!obtenerEntrada(option)) {
            std::cout << "Entrada inválida. Por favor, introduce un número.\n";
            continue; // Vuelve al menú principal
        }

   

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
