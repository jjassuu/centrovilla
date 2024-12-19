#ifndef DOCTOR_H
#define DOCTOR_H

#include "person.h"
#include <fstream>
#include <string>
#include <iostream>

// Clase Doctor
class Doctor : public Person {
public:
    int doctorID;
    string especialidad;  
    string disponibilidad;    

    void añadirDoctor() {
        std::cout << "Introduce el DNI del doctor: ";
        std::cin >> doctorID;
        getPersonData();
        std::cout << "Especializacion: ";
        std::cin.ignore();
        getline(std::cin, especialidad);
        std::cout << "Disponibilidad (Ej: Mañana/Tarde/Noche): ";
        getline(std::cin, disponibilidad);

        ofstream file("doctors.txt", ios::app);
        file << doctorID << ";" << nombre << ";" << ntelf << ";"
            << especialidad << ";" << disponibilidad << "\n";
        file.close();
        std::cout << "Doctor registrado con éxito.\n";
    }

    static void mostrarDoctor() {
        ifstream file("doctors.txt");
        string line;
        cout << "\n--- Lista de Doctores ---\n";
        while (getline(file, line)) {
            std::cout << line << endl;
        }
        file.close();
    }
}
;
#endif
