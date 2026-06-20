#include "Calculadoras.h"
#include <iostream>
using namespace std;

// Calculadora Base 

float Calculadora::sumar()                          { return 0 + 0; }
float Calculadora::sumar(float a, float b)           { return a + b; }
float Calculadora::sumar(float a, float b, float c)  { return a + b + c; }

float Calculadora::restar(float a, float b)          { return a - b; }

float Calculadora::multiplicar(float a, float b)          { return a * b; }
float Calculadora::multiplicar(float a, float b, float c) { return a * b * c; }

float Calculadora::dividir(float a, float b) {
    if (b == 0) {
        cout << "  [Error] Division entre cero no permitida.\n";
        return 0;
    }
    return a / b;
}

void Calculadora::mostrarMenu() {
    cout << "\n--- Calculadora Base ---\n"
         << "1. Sumar\n"
         << "2. Restar\n"
         << "3. Multiplicar\n"
         << "4. Dividir\n";
}

// Calculadora Nueva 

float CalculadoraNueva::multiplicar(float a, float b) {
    if (b == 0 || a == 0) return 0;
    bool negativo = (a < 0) != (b < 0);
    float absA = (a < 0) ? -a : a;
    float absB = (b < 0) ? -b : b;
    float resultado = 0;
    for (int i = 0; i < (int)absB; i++)
        resultado += absA;
    return negativo ? -resultado : resultado;
}

float CalculadoraNueva::multiplicarRecursivo(float a, float b) {
    if (b == 0) return 0;
    if (b < 0)  return -multiplicarRecursivo(a, -b);
    return a + multiplicarRecursivo(a, b - 1);
}

float CalculadoraNueva::potencia(float base, int exp) {
    if (exp == 0) return 1;
    float resultado = 1;
    for (int i = 0; i < exp; i++)
        resultado = multiplicar(resultado, base);
    return resultado;
}

float CalculadoraNueva::potenciaRecursiva(float base, int exp) {
    if (exp == 0) return 1;
    return multiplicarRecursivo(base, potenciaRecursiva(base, exp - 1));
}

float CalculadoraNueva::dividir(float a, float b) {
    if (b == 0) {
        cout << "  [Error] Division entre cero no permitida.\n";
        return 0;
    }
    bool negativo = (a < 0) != (b < 0);
    float absA = (a < 0) ? -a : a;
    float absB = (b < 0) ? -b : b;
    int cociente = 0;
    while (absA >= absB) {
        absA -= absB;
        cociente++;
    }
    return negativo ? -(float)cociente : (float)cociente;
}

int CalculadoraNueva::dividirRecursivo(float a, float b) {
    if (b == 0) { cout << "  [Error] Division entre cero.\n"; return 0; }
    if (a < b)  return 0;
    return 1 + dividirRecursivo(a - b, b);
}

void CalculadoraNueva::mostrarMenu() {
    cout << "\n--- Calculadora Nueva (Herencia + Sobreescritura) ---\n"
         << "1. Sumar\n"
         << "2. Restar\n"
         << "3. Multiplicar (por sumas sucesivas)\n"
         << "4. Dividir     (por restas sucesivas)\n"
         << "5. Potencia    (por multiplicaciones sucesivas)\n"
         << "6. Multiplicar RECURSIVO\n"
         << "7. Potencia    RECURSIVA\n"
         << "8. Dividir     RECURSIVO\n";
}
