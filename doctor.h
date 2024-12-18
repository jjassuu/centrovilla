#ifndef DOCTOR_H
#define DOCTOR_H

#include "person.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

// Clase Doctor
class Doctor : public Person {
public:
    int doctorID;
    string especialidad;  
    string disponibilidad;    

    void a�adirDoctor() {
        cout << "Introduce el ID del doctor: ";
        cin >> doctorID;
        getPersonData();
        cout << "Especializaci�n: ";
        cin.ignore();
        getline(cin, especialidad);
        cout << "Disponibilidad (Ej: Ma�ana/Tarde/Noche): ";
        getline(cin, disponibilidad);

        ofstream file("doctors.txt", ios::app);
        file << doctorID << ";" << nombre << ";" << ntelf << ";"
            << especialidad << ";" << disponibilidad << "\n";
        file.close();
        cout << "Doctor registrado con �xito.\n";
    }

    static void mostrarDoctor() {
        ifstream file("doctors.txt");
        string line;
        cout << "\n--- Lista de Doctores ---\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
};

#endif
