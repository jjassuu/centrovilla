#ifndef CITA_H
#define CITA_H

#include <string>
#include <fstream>
#include <iostream>

class Cita {
public:
    void programarcita(int pacienteID, int doctorID, const std::string& fecha, const std::string& hora);
    static void mostrarcitas();
};

#endif
