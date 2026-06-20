#ifndef CALCULADORAS_H
#define CALCULADORAS_H

// Calculadora Base 

class Calculadora {
public:
    float sumar();
    float sumar(float a, float b);
    float sumar(float a, float b, float c);

    float restar(float a, float b);

    virtual float multiplicar(float a, float b);
    float multiplicar(float a, float b, float c);

    virtual float dividir(float a, float b);

    virtual void mostrarMenu();
};

// Calculadora Nueva 

class CalculadoraNueva : public Calculadora {
public:
    float multiplicar(float a, float b) override;
    float multiplicarRecursivo(float a, float b);

    float potencia(float base, int exp);
    float potenciaRecursiva(float base, int exp);

    float dividir(float a, float b) override;
    int   dividirRecursivo(float a, float b);

    void mostrarMenu() override;
};

#endif
