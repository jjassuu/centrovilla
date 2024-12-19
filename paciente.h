#ifndef PACIENTE_H
#define PACIENTE_H

#include "person.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

// Clase Paciente
class Paciente : public Person {
public:
    int pacienteID;
    string dolencia;
    string diacita;

    void añadirpaciente() {
        cout << "Introduce el DNI del paciente: ";
        cin >> pacienteID;
        getPersonData();
        cout << "Introduce la dolencia del paciente: ";
        cin.ignore();
        getline(cin, dolencia);
        cout << "Introduce la fecha de la cita (YYYY-MM-DD): ";
        cin >> diacita;

        ofstream file("patients.txt", ios::app);
        file << pacienteID << ";" << nombre << ";" << ntelf << ";"
            << dolencia << ";" << diacita << "\n";
        file.close();
        cout << "Paciente registrado con éxito.\n";
    }

    static void mostarpacientes() {
        ifstream file("patients.txt");
        string line;
        cout << "\n--- Lista de Pacientes ---\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
}

;
#endif
