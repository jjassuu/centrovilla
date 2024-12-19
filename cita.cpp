#include "cita.h"

void Cita::programarcita(int pacienteID, int doctorID, const std::string& fecha, const std::string& hora) {
    std::ofstream file("citas.txt", std::ios::app);
    if (file.is_open()) {
        file << pacienteID << ";" << doctorID << ";" << fecha << ";" << time << "\n";
        file.close();
        std::cout << "Cita asignada correctamente.\n";
    }
    else {
        std::cerr << "Error al abrir el archivo de citas.\n";
    }
}

void Cita::mostrarcitas() {
    std::ifstream file("citas.txt");
    std::string line;
    std::cout << "\n--- Lista de Citas ---\n";
    if (file.is_open()) {
        while (getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Error al abrir el archivo de citas.\n";
    }
}
