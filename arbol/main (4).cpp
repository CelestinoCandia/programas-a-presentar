#include <iostream>
#include "Arbol.h"
using namespace std;

int main() {
    Arbol arbol;
    int opcion;

    do {
        cout << "\nARBOL BINARIO DE AUTOS\n";
        cout << "1. Insertar auto\n";
        cout << "2. Mostrar InOrden\n";
        cout << "3. Convertir arbol\n";
        cout << "4. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                arbol.insertar();
                break;

            case 2:
                arbol.mostrarInOrden();
                break;

            case 3:
                arbol.convertir();
                break;

            case 4:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 4);

    return 0;
}