#include "Historial.h"

// Definicion real de las variables globales 
std::vector<RegistroOperacion> historialOperaciones;
std::vector<RegistroAuto>      historialAutos;
std::vector<RegistroPersona>   historialPersonas;

void registrarOperacion(float n1, float n2, char op, float res, std::string calc) {
    RegistroOperacion r;
    r.num1 = n1;
    r.num2 = n2;
    r.operacion = op;
    r.resultado = res;
    r.calculadora = calc;
    historialOperaciones.push_back(r);
}

void registrarAuto(std::string marca, float precio, int anio, std::string version) {
    RegistroAuto r;
    r.marca = marca;
    r.precio = precio;
    r.anio = anio;
    r.version = version;
    historialAutos.push_back(r);
}

void registrarPersona(std::string nombre, std::string ap, std::string am, char genero, int edad, std::string version) {
    RegistroPersona r;
    r.nombre = nombre;
    r.apellidoPaterno = ap;
    r.apellidoMaterno = am;
    r.genero = genero;
    r.edad = edad;
    r.version = version;
    historialPersonas.push_back(r);
}
