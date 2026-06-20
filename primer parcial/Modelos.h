#ifndef MODELOS_H
#define MODELOS_H

#include <string>

// PR

struct Auto {
    std::string marca;
    float       precio;
    int         anio;
};

struct Persona {
    std::string nombre;
    std::string apellidoPaterno;
    std::string apellidoMaterno;
    char        genero;
    int         edad;
};

void mostrarAuto(const Auto& a);
void mostrarPersona(const Persona& p);

// PO

class AutoPOO {
private:
    std::string marca;
    float       precio;
    int         anio;
public:
    AutoPOO(std::string m, float p, int a);
    void mostrar() const;
    std::string getMarca()  const { return marca; }
    float       getPrecio() const { return precio; }
    int         getAnio()   const { return anio; }
};

class PersonaPOO {
private:
    std::string nombre;
    std::string apellidoPaterno;
    std::string apellidoMaterno;
    char        genero;
    int         edad;
public:
    PersonaPOO(std::string n, std::string ap, std::string am, char g, int e);
    void mostrar() const;
    std::string getNombre() const { return nombre; }
    char        getGenero() const { return genero; }
    int         getEdad()   const { return edad; }
};

//  Recursividad 

long long factorial(int n);
long long fibonacci(int n);

#endif
