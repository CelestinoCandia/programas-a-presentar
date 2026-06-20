#include <iostream>
#include <limits>
#include "Modelos.h"
#include "Calculadoras.h"
#include "Exportador.h"
#include "Historial.h"
using namespace std;


void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

float pedirNumero(const string& msg) {
    float n;
    cout << msg;
    while (!(cin >> n)) {
        cout << "  Entrada invalida. " << msg;
        cin.clear();
        limpiarBuffer();
    }
    return n;
}

int pedirEntero(const string& msg) {
    int n;
    cout << msg;
    while (!(cin >> n)) {
        cout << "  Entrada invalida. " << msg;
        cin.clear();
        limpiarBuffer();
    }
    return n;
}



void demoTiposDeDato() {
    int sub;
    cout << "\n Tipos de dato (Ejercicio 7) \n"
         << "1. Crear Auto (version PE - struct)\n"
         << "2. Crear Persona (version PE - struct)\n"
         << "3. Crear Auto (version POO - class)\n"
         << "4. Crear Persona (version POO - class)\n"
         << "5. Ver tamanos de tipos (sizeof)\n"
         << "Opcion: ";
    cin >> sub;
    limpiarBuffer();

    if (sub == 1) {
        Auto a;
        cout << "  Marca: ";
        getline(cin, a.marca);
        a.precio = pedirNumero("  Precio: ");
        a.anio   = pedirEntero("  Año: ");

        cout << "\n[Auto creado - PE]\n";
        mostrarAuto(a);
        registrarAuto(a.marca, a.precio, a.anio, "PE");

    } else if (sub == 2) {
        Persona p;
        cout << "  Nombre: ";
        getline(cin, p.nombre);
        cout << "  Apellido paterno: ";
        getline(cin, p.apellidoPaterno);
        cout << "  Apellido materno: ";
        getline(cin, p.apellidoMaterno);
        cout << "  Genero (M/F): ";
        cin >> p.genero;
        p.edad = pedirEntero("  Edad: ");

        cout << "\n[Persona creada - PE]\n";
        mostrarPersona(p);
        registrarPersona(p.nombre, p.apellidoPaterno, p.apellidoMaterno, p.genero, p.edad, "PE");

    } else if (sub == 3) {
        string marca;
        cout << "  Marca: ";
        getline(cin, marca);
        float precio = pedirNumero("  Precio: ");
        int   anio   = pedirEntero("  Año: ");

        AutoPOO a(marca, precio, anio);
        cout << "\n[Auto creado - POO]\n";
        a.mostrar();
        registrarAuto(a.getMarca(), a.getPrecio(), a.getAnio(), "POO");

    } else if (sub == 4) {
        string nombre, ap, am;
        char genero;
        cout << "  Nombre: ";
        getline(cin, nombre);
        cout << "  Apellido paterno: ";
        getline(cin, ap);
        cout << "  Apellido materno: ";
        getline(cin, am);
        cout << "  Genero (M/F): ";
        cin >> genero;
        int edad = pedirEntero("  Edad: ");

        PersonaPOO p(nombre, ap, am, genero, edad);
        cout << "\n[Persona creada - POO]\n";
        p.mostrar();
        registrarPersona(p.getNombre(), ap, am, p.getGenero(), p.getEdad(), "POO");

    } else if (sub == 5) {
        cout << "\n[Tamanos de tipos basicos y creados]\n"
             << "  int       : " << sizeof(int)       << " bytes\n"
             << "  float     : " << sizeof(float)     << " bytes\n"
             << "  double    : " << sizeof(double)    << " bytes\n"
             << "  char      : " << sizeof(char)      << " bytes\n"
             << "  bool      : " << sizeof(bool)      << " bytes\n"
             << "  Auto      : " << sizeof(Auto)      << " bytes (struct)\n"
             << "  Persona   : " << sizeof(Persona)   << " bytes (struct)\n"
             << "  AutoPOO   : " << sizeof(AutoPOO)   << " bytes (class)\n"
             << "  PersonaPOO: " << sizeof(PersonaPOO)<< " bytes (class)\n";
    } else {
        cout << "  Opcion invalida.\n";
    }
}

void  demoRecursividad() {
    int n = pedirEntero("Ingresa un numero para Factorial y Fibonacci: ");

    long long fact = factorial(n);
    long long fib  = fibonacci(n);>

    cout << "  Factorial(" << n << ") = " << fact << "\n"
         << "  Fibonacci(" << n << ") = " << fib << "\n";

    registrarOperacion(n, 0, '!', fact, "Recursividad-Factorial");
    registrarOperacion(n, 0, 'F', fib, "Recursividad-Fibonacci");
}

// Menu

void menuCalculadoraBase() {
    Calculadora calc;
    int op;
    do {
        calc.mostrarMenu();
        cout << "0. Volver\nOpcion: ";
        cin >> op;

        float a, b, c;
        switch (op) {
            case 1:
                cout << "  (1) Sin parametros -> " << calc.sumar() << "\n";
                a = pedirNumero("  a: "); b = pedirNumero("  b: ");
                cout << "  (2 params) " << a << " + " << b << " = " << calc.sumar(a, b) << "\n";
                registrarOperacion(a, b, '+', calc.sumar(a, b), "Base");
                c = pedirNumero("  c: ");
                cout << "  (3 params) " << a << " + " << b << " + " << c << " = " << calc.sumar(a, b, c) << "\n";
                break;
            case 2:
                a = pedirNumero("  a: "); b = pedirNumero("  b: ");
                cout << "  " << a << " - " << b << " = " << calc.restar(a, b) << "\n";
                registrarOperacion(a, b, '-', calc.restar(a, b), "Base");
                break;
            case 3:
                a = pedirNumero("  a: "); b = pedirNumero("  b: ");
                cout << "  " << a << " * " << b << " = " << calc.multiplicar(a, b) << "\n";
                registrarOperacion(a, b, '*', calc.multiplicar(a, b), "Base");
                c = pedirNumero("  c: ");
                cout << "  " << a << " * " << b << " * " << c << " = " << calc.multiplicar(a, b, c) << "\n";
                break;
            case 4:
                a = pedirNumero("  a: "); b = pedirNumero("  b: ");
                cout << "  " << a << " / " << b << " = " << calc.dividir(a, b) << "\n";
                registrarOperacion(a, b, '/', calc.dividir(a, b), "Base");
                break;
            case 0: break;
            default: cout << "  Opcion invalida.\n";
        }
    } while (op != 0);
}

void menuCalculadoraNueva() {
    CalculadoraNueva calc;
    int op;
    do {
        calc.mostrarMenu();
        cout << "0. Volver\nOpcion: ";
        cin >> op;

        float a, b;
        int   exp;
        switch (op) {
            case 1:
                a = pedirNumero("  a: "); b = pedirNumero("  b: ");
                cout << "  " << a << " + " << b << " = " << calc.sumar(a, b) << "\n";
                registrarOperacion(a, b, '+', calc.sumar(a, b), "Nueva");
                break;
            case 2:
                a = pedirNumero("  a: "); b = pedirNumero("  b: ");
                cout << "  " << a << " - " << b << " = " << calc.restar(a, b) << "\n";
                registrarOperacion(a, b, '-', calc.restar(a, b), "Nueva");
                break;
            case 3:
                a = pedirNumero("  a: "); b = pedirNumero("  b (entero): ");
                cout << "  " << a << " * " << (int)b << " (por sumas) = " << calc.multiplicar(a, (int)b) << "\n";
                registrarOperacion(a, b, '*', calc.multiplicar(a, (int)b), "Nueva");
                break;
            case 4:
                a = pedirNumero("  a: "); b = pedirNumero("  b (entero): ");
                cout << "  " << a << " / " << (int)b << " (por restas) = " << calc.dividir(a, (int)b) << "\n";
                registrarOperacion(a, b, '/', calc.dividir(a, (int)b), "Nueva");
                break;
            case 5:
                a = pedirNumero("  base: "); exp = pedirEntero("  exponente: ");
                cout << "  " << a << "^" << exp << " (por mults) = " << calc.potencia(a, exp) << "\n";
                registrarOperacion(a, exp, '^', calc.potencia(a, exp), "Nueva");
                break;
            case 6:
                a = pedirNumero("  a: "); b = pedirNumero("  b (entero): ");
                cout << "  " << a << " * " << (int)b << " (recursivo) = " << calc.multiplicarRecursivo(a, (int)b) << "\n";
                registrarOperacion(a, b, '*', calc.multiplicarRecursivo(a, (int)b), "Nueva-Recursivo");
                break;
            case 7:
                a = pedirNumero("  base: "); exp = pedirEntero("  exponente: ");
                cout << "  " << a << "^" << exp << " (recursivo) = " << calc.potenciaRecursiva(a, exp) << "\n";
                registrarOperacion(a, exp, '^', calc.potenciaRecursiva(a, exp), "Nueva-Recursivo");
                break;
            case 8:
                a = pedirNumero("  a: "); b = pedirNumero("  b (entero): ");
                cout << "  " << a << " / " << (int)b << " (recursivo) = " << calc.dividirRecursivo(a, (int)b) << "\n";
                registrarOperacion(a, b, '/', calc.dividirRecursivo(a, (int)b), "Nueva-Recursivo");
                break;
            case 0: break;
            default: cout << "  Opcion invalida.\n";
        }
    } while (op != 0);
}

void menuExportar() {
    int op;
    do {
        cout << "\n Exportar datos \n"
             << "1. TXT\n"
             << "2. JSON\n"
             << "3. CSV\n"
             << "4. XML\n"
             << "5. Todos\n"
             << "0. Salir sin exportar\n"
             << "Opcion: ";
        cin >> op;

        switch (op) {
            case 1: generarTXT();  break;
            case 2: generarJSON(); break;
            case 3: generarCSV();  break;
            case 4: generarXML();  break;
            case 5:
                generarTXT();
                generarJSON();
                generarCSV();
                generarXML();
                cout << "Todos los archivos generados!\n";
                break;
            case 0: break;
            default: cout << "Opcion invalida.\n";
        }
    } while (op != 0);
}

//  Main 

int main() {
    int opcion;
    do {
        cout << "\n MENU PRINCIPAL \n"
             << "1. Calculadora Base\n"
             << "2. Calculadora Nueva\n"
             << "3. Tipos de dato\n"
             << "4. Recursividad\n"
             << "5. Exportar datos\n"
             << "0. Salir\n"
             << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuCalculadoraBase();  break;
            case 2: menuCalculadoraNueva(); break;
            case 3: demoTiposDeDato();      break;
            case 4: demoRecursividad();     break;
            case 5: menuExportar();         break;
            case 0: cout << "Hasta luego!\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
