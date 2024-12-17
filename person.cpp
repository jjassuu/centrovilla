#include "person.h"  
// Implementación de los métodos de la clase Person
void Person::getPersonData() {
    cout << "Introduce la edad: ";
    cin >> edad;
    cin.ignore(); 
    cout << "Introduce el nombre: ";
    getline(cin, nombre);
    cout << "Número de teléfono: ";
    getline(cin, ntelf);
    cout << "Domicilio: ";
    getline(cin, direccion);
    cout << "Email: ";
    getline(cin, email);
}

void Person::showPersonData() const {
    cout << "Edad: " << edad << ", Nombre: " << nombre
        << ", Número telf: " << ntelf << ", Dirección: " << direccion
        << ", Email: " << email << endl;
}
