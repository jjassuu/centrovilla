#include "person.h"  
// Implementaci�n de los m�todos de la clase Person
void Person::getPersonData() {
    cout << "Introduce la edad: ";
    cin >> edad;
    cin.ignore(); 
    cout << "Introduce el nombre: ";
    getline(cin, nombre);
    cout << "N�mero de tel�fono: ";
    getline(cin, ntelf);
    cout << "Domicilio: ";
    getline(cin, direccion);
    cout << "Email: ";
    getline(cin, email);
}

void Person::showPersonData() const {
    cout << "Edad: " << edad << ", Nombre: " << nombre
        << ", N�mero telf: " << ntelf << ", Direcci�n: " << direccion
        << ", Email: " << email << endl;
}
