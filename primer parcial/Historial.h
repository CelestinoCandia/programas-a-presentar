#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <string>
#include <vector>

//  Estructuras de registro 

struct RegistroOperacion {
    float num1;
    float num2;
    char  operacion;   // '+', '-', '*', '/'
    float resultado;
    std::string calculadora; // "Base" o "Nueva"
};

struct RegistroAuto {
    std::string marca;
    float       precio;
    int         anio;
    std::string version; // "PE" o "POO"
};

struct RegistroPersona {
    std::string nombre;
    std::string apellidoPaterno;
    std::string apellidoMaterno;
    char        genero;
    int         edad;
    std::string version; // "PE" o "POO"
};

//  Historial global de la sesion 

extern std::vector<RegistroOperacion> historialOperaciones;
extern std::vector<RegistroAuto>      historialAutos;
extern std::vector<RegistroPersona>   historialPersonas;

void registrarOperacion(float n1, float n2, char op, float res, std::string calc);
void registrarAuto(std::string marca, float precio, int anio, std::string version);
void registrarPersona(std::string nombre, std::string ap, std::string am, char genero, int edad, std::string version);

#endif
