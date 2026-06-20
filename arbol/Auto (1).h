#ifndef AUTO_H
#define AUTO_H

#include <iostream>
#include <string>
using namespace std;

class Auto {
private:
    string marca;
    float precio;
    int anio;

public:
    void capturar() {
        cout << "Marca: ";
        cin >> marca;

        cout << "Precio: ";
        cin >> precio;

        cout << "Anio: ";
        cin >> anio;
    }

    void mostrar() {
        cout << "Marca: " << marca << endl;
        cout << "Precio: $" << precio << endl;
        cout << "Anio: " << anio << endl;
    }

    string getMarca() {
        return marca;
    }

    float getPrecio() {
        return precio;
    }

    int getAnio() {
        return anio;
    }
};

#endif