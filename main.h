// CMakeProject6.h: archivo de inclusión para archivos de inclusión estándar del sistema,
// o archivos de inclusión específicos de un proyecto.

#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <limits>

template <typename T>
bool obtenerEntrada(T& entrada) {
    std::cin >> entrada;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

#endif

// TODO: Haga referencia aquí a los encabezados adicionales que el programa requiere.
