#include "Modelos.h"
#include <iostream>
using namespace std;

//  Tipos de dato 

void mostrarAuto(const Auto& a) {
    cout << "  Marca  : " << a.marca  << "\n"
         << "  Precio : $" << a.precio << "\n"
         << "  Año   : " << a.anio   << "\n";
}

void mostrarPersona(const Persona& p) {
    cout << "  Nombre : " << p.nombre << " " << p.apellidoPaterno << " " << p.apellidoMaterno << "\n"
         << "  Genero : " << p.genero << "\n"
         << "  Edad   : " << p.edad   << " anos\n";
}

//  Tipos de dato - Version POO 

AutoPOO::AutoPOO(string m, float p, int a) : marca(m), precio(p), anio(a) {}

void AutoPOO::mostrar() const {
    cout << "  Marca  : " << marca  << "\n"
         << "  Precio : $" << precio << "\n"
         << "  Año   : " << anio   << "\n";
}

PersonaPOO::PersonaPOO(string n, string ap, string am, char g, int e)
    : nombre(n), apellidoPaterno(ap), apellidoMaterno(am), genero(g), edad(e) {}

void PersonaPOO::mostrar() const {
    cout << "  Nombre : " << nombre << " " << apellidoPaterno << " " << apellidoMaterno << "\n"
         << "  Genero : " << genero << "\n"
         << "  Edad   : " << edad   << " anos\n";
}

// Recursividad 

long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

long long fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
