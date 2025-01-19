#include "usuarios.h"
#include "doctor.h"
#include "admin.h"
#include "person.h"
#include "paciente.h"
#include "main.h"
#include "backupmanager.h"
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
        std::cout << "5. Gestion de Backups\n";
        std::cout << "6. Cerrar sesion\n";
        std::cout << "Elige una opcion: ";

        if (!obtenerEntrada(option)) {
            std::cout << "Entrada invalida. Por favor, introduce un numero.\n";
            continue; // Vuelve al menu principal
        }

        switch (option) {
        case 1:
        {
            int doctorOption;
            std::cout << "\n1. Añadir Doctor\n";
            std::cout << "2. Ver Todos los Doctores\n";
            std::cout << "3. Eliminar Doctor\n";
            std::cout << "4. Editar Doctor\n";
            std::cout << "Elige una opcion: ";
            if (!obtenerEntrada(doctorOption)) {
                std::cout << "Entrada invalida. Por favor, introduce un numero.\n";
                break; // Regresa al menu principal
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
                cout << "Opcion invalida.\n";
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
            std::cout << "8. Derivar Paciente\n";
            std::cout << "Elige una opcion\n";
            if (!obtenerEntrada(opcionpaciente)) {
                std::cout << "Entrada invalida. Por favor, introduce un numero.\n";
                break; // Regresa al menu principal
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

                bool dniValido = false;

                do {
                    std::cout << "Introduce el DNI del paciente a buscar: ";
                    std::getline(std::cin >> std::ws, dni); 

                    if (dni.empty()) {
                        std::cerr << "Error: El DNI no puede estar vacio. Por favor, intentalo de nuevo.\n";
                        continue; 
                    }

                    if (!Person::validarDNI(dni)) {
                        std::cerr << "Error: El DNI ingresado no tiene un formato valido. Debe contener 8 numeros seguidos de una letra.\n";
                        continue; 
                    }

                    dniValido = true;

                } while (!dniValido); 

                Paciente::buscarPaciente(dni);
            }
            else if (opcionpaciente == 4) {
                std::string dni, fecha, descripcion, medico;

                do {
                    std::cout << "Introduce el DNI del paciente: ";
                    std::getline(std::cin >> std::ws, dni);

                    if (dni.empty()) {
                        std::cerr << "Error: El DNI no puede estar vacio. Por favor, intentalo de nuevo.\n";
                        continue;
                    }

                    if (!Person::validarDNI(dni)) {
                        std::cerr << "Error: El DNI ingresado no tiene un formato valido. Debe contener 8 numeros seguidos de una letra.\n";
                        continue;
                    }

                    if (!Paciente::existePaciente(dni)) {
                        std::cerr << "Error: El paciente con DNI " << dni << " no esta registrado. Por favor, verifica los datos.\n";
                        continue;
                    }

                    break; // Salimos del bucle si todo es valido
                } while (true);

                // Validacion de la fecha
                do {
                    std::cout << "Introduce la fecha (YYYY-MM-DD): ";
                    std::getline(std::cin >> std::ws, fecha);

                    if (fecha.empty()) {
                        std::cerr << "Error: La fecha no puede estar vacia. Por favor, intentalo de nuevo.\n";
                        continue;
                    }

                    if (!GestionCitas::validarFecha(fecha)) {
                        std::cerr << "Error: La fecha no tiene un formato valido. Ejemplo: 2025-01-19.\n";
                        continue;
                    }

                    break; 
                } while (true);

                do {
                    std::cout << "Introduce la descripcion de la dolencia: ";
                    std::getline(std::cin >> std::ws, descripcion);

                    if (descripcion.empty()) {
                        std::cerr << "Error: La descripcion no puede estar vacia. Por favor, intentalo de nuevo.\n";
                        continue;
                    }

                    break; // Salimos del bucle si la descripcion es valida
                } while (true);

                do {
                    std::cout << "Introduce el nombre del medico: ";
                    std::getline(std::cin >> std::ws, medico);

                    if (medico.empty()) {
                        std::cerr << "Error: El nombre del medico no puede estar vacio. Por favor, intentalo de nuevo.\n";
                        continue;
                    }

                    break; 
                } while (true);

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

                while (true) {
                    std::cout << "Introduce el DNI del paciente a editar: ";
                    std::getline(std::cin >> std::ws, dni);

                    if (dni.empty()) {
                        std::cerr << "Error: El DNI no puede estar vacio. Por favor, intentalo de nuevo.\n";
                        continue;
                    }

                    if (!Person::validarDNI(dni)) {
                        std::cerr << "Error: El DNI ingresado no tiene un formato valido. Debe contener 8 numeros seguidos de una letra.\n";
                        continue;
                    }

                    if (!Paciente::existePaciente(dni)) {
                        std::cerr << "Error: Paciente con DNI " << dni << " no encontrado.\n";
                        continue;
                    }

                    break;
                }

                Paciente paciente;
                paciente.editarPaciente(dni);
                }

            else if (opcionpaciente == 7) {
                std::string dni;

                while (true) {
                    std::cout << "Introduce el DNI del paciente a eliminar: ";
                    std::getline(std::cin >> std::ws, dni);

                    if (dni.empty()) {
                        std::cerr << "Error: El DNI no puede estar vacio. Por favor, intentalo de nuevo.\n";
                        continue;
                    }

                    if (!Person::validarDNI(dni)) {
                        std::cerr << "Error: El DNI ingresado no tiene un formato valido. Debe contener 8 numeros seguidos de una letra.\n";
                        continue;
                    }

                    if (!Paciente::existePaciente(dni)) {
                        std::cerr << "Error: Paciente con DNI " << dni << " no encontrado.\n";
                        continue;
                    }

                    break;
                }

                Paciente::eliminarPaciente(dni);
            }
            else if (opcionpaciente == 8) {
                std::string dni;
                int centroOpcion;
                std::cout << "Introduce el DNI del paciente a derivar: ";
                std::cin >> dni;

                if (!Paciente::existePaciente(dni)) {
                    std::cout << "Error: El paciente con DNI " << dni << " no esta registrado. Derivacion cancelada.\n";
                    break;
                }

                std::cout << "\nCentros Asociados:\n";
                std::cout << "1. Centro de Salud Mental\n";
                std::cout << "2. Centro de Traumatologia\n";
                std::cout << "Elige un centro: ";
                if (!obtenerEntrada(centroOpcion) || (centroOpcion != 1 && centroOpcion != 2)) {
                    std::cout << "Opcion invalida. Derivacion cancelada.\n";
                    break;
                }

                std::string centro = (centroOpcion == 1) ? "Salud Mental" : "Traumatologia";

                Paciente paciente;
                paciente.derivarPaciente(centro);
                break;
            }
            else {
                std::cout << "Opcion invalida.\n";
            }
            break;
        }
        case 3: {
            int citaOpcion;
            std::cout << "\n1. Agendar Cita\n";
            std::cout << "2. Ver Todas las Citas\n";
            std::cout << "3. Ver Citas por Dia\n";
            std::cout << "4. Ver Citas por Turno\n";
            std::cout << "5. Generar Reporte por Dia\n";
            std::cout << "6. Eliminar Cita\n";
            std::cout << "7. Modificar Cita\n"; 
            std::cout << "Elige una opcion: ";
            if (!obtenerEntrada(citaOpcion)) {
                std::cout << "Entrada invalida. Por favor, introduce un numero.\n";
                break; 
            }

            GestionCitas gestionCitas;

            if (citaOpcion == 1) {
                gestionCitas.agendarCita("", "", "", "", "");
            }
            else if (citaOpcion == 2) {
                gestionCitas.mostrarTodasLasCitas();
            }
            else if (citaOpcion == 3) {
                std::string fecha;
                std::cout << "Introduce la Fecha (YYYY-MM-DD): ";
                std::cin >> fecha;
                gestionCitas.listarCitasPorDia(fecha);
            }
            else if (citaOpcion == 4) {
                std::string turno;
                std::cout << "Introduce el turno (mañana/tarde): ";
                std::cin >> turno;
                gestionCitas.listarCitasPorTurno(turno);
            }
            else if (citaOpcion == 5) {
                std::string fecha;
                std::cout << "Introduce la Fecha (YYYY-MM-DD): ";
                std::cin >> fecha;
                gestionCitas.generarReportePorDia(fecha);
            }
            else if (citaOpcion == 6) {
                std::string dniPaciente, fecha, hora;
                std::cout << "Introduce el DNI del Paciente: ";
                std::cin >> dniPaciente;
                std::cout << "Introduce la Fecha (YYYY-MM-DD): ";
                std::cin >> fecha;
                std::cout << "Introduce la Hora (HH:MM): ";
                std::cin >> hora;

                gestionCitas.eliminarCita(dniPaciente, fecha, hora);
            }
            else if (citaOpcion == 7) {
                std::string dniPaciente, fechaActual, horaActual;
                std::cout << "Introduce el DNI del Paciente: ";
                std::cin >> dniPaciente;
                std::cout << "Introduce la Fecha actual de la cita (YYYY-MM-DD): ";
                std::cin >> fechaActual;
                std::cout << "Introduce la Hora actual de la cita (HH:MM): ";
                std::cin >> horaActual;

                gestionCitas.modificarCita(dniPaciente, fechaActual, horaActual);
            }
            else {
                std::cout << "Opcion invalida. Intentalo de nuevo.\n";
            }
            break;
        }
        case 4: {
            int adminOpcion;
            std::cout << "\n1. Añadir Administrador\n";
            std::cout << "2. Ver Todos los Administradores\n";
            std::cout << "3. Eliminar Administrador\n";
            std::cout << "4. Editar Administrador\n";
            std::cout << "Elige una opcion: ";
            if (!obtenerEntrada(adminOpcion)) {
                std::cout << "Entrada invalida. Por favor, introduce un numero.\n";
                break; // Regresa al menu principal
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
                std::cout << "Opcion invalida.\n";
            }
            break;
        }case 5: {
      
            int backupOption;
            std::cout << "\n1. Crear Backups de Todos los Archivos\n";
            std::cout << "2. Listar Backups Disponibles\n";
            std::cout << "3. Restaurar un Archivo\n";
            std::cout << "Elige una opcion: ";

            if (!obtenerEntrada(backupOption)) {
                std::cout << "Entrada invalida, introduzca un numero";
                break;
            }

            if (backupOption == 1) {
                // Crear backups de todos los archivos
                BackupManager backupManager("./backups");
                std::vector<std::string> archivos = { "pacientes.csv", "doctor.csv", "citas.csv", "derivaciones.csv" };
                for (const auto& archivo : archivos) {
                    backupManager.crearBackup(archivo);
                }
            }
            else if (backupOption == 2) {
                // Listar archivos de backup disponibles
                BackupManager backupManager("./backups");
                std::vector<std::string> backups = backupManager.listarBackups();
                if (backups.empty()) {
                    std::cout << "No hay backups disponibles.\n";
                }
                else {
                    std::cout << "Archivos de Backup Disponibles:\n";
                    for (const auto& backup : backups) {
                        std::cout << "- " << backup << "\n";
                    }
                }
            }
            else if (backupOption == 3) {
                // Restaurar un archivo desde un backup
                BackupManager backupManager("./backups");
                std::string archivoOriginal, archivoBackup;
                std::cout << "Introduce el nombre del archivo original (e.g., pacientes.csv): ";
                std::cin >> archivoOriginal;
                std::cout << "Introduce el nombre del archivo de backup (e.g., pacientes.csv.bak): ";
                std::cin >> archivoBackup;
                backupManager.restaurarBackup(archivoOriginal, archivoBackup);
            }
            else {
                std::cout << "Opcion invalida.\n";
            }
            break;
        }
        case 6:
            std::cout << "Cerrando sesion...\n";
            return; 
        default:
            std::cout << "Opcion invalida. Intentalo de nuevo.\n";
            break;
        }
    } while (option != 5);
}


int main() {

    std::unordered_map<std::string, std::string> users;
    cargarusuario(users);

    int option;
    bool loggedIn = false; // Para controlar la sesion

    do {
        std::cout << "\n=== Bienvenido al Centro de Salud Villa ===\n";
        std::cout << "1. Iniciar sesion\n";
        std::cout << "2. Registrar usuario\n";
        std::cout << "3. Salir\n";
        std::cout << "Elige una opcion: ";

        if (!obtenerEntrada(option)) {
            std::cout << "Entrada invalida. Por favor, introduce un numero.\n";
            continue; // Vuelve al menu principal
        }

   

        switch (option) {
        case 1:
            if (login(users)) {
                loggedIn = true;
                mainMenu(); // Acceder al menu principal
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
            std::cout << "Opcion invalida. Intentalo de nuevo.\n";
            break;
        }
    } while (option != 3 && !loggedIn); // Detener el bucle correctamente

    return 0;
}
 