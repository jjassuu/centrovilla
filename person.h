#ifndef PERSON_H   
#define PERSON_H

#include <string>
#include <iostream>
using namespace std;

// Declaración de la clase Person
class Person {
protected:
    int edad=0;
    string nombre, ntelf, direccion, email;

public:
    void getPersonData();
    void showPersonData() const;
};

#endif
