#include <iostream>
#include "Lista.h"
using namespace std;

int main() {
    Lista lista;
    int opcion;

    do {
        cout << "\n===== LISTA DINAMICA DE AUTOS =====\n";
        cout << "1. Insertar auto\n";
        cout << "2. Mostrar autos\n";
        cout << "3. Eliminar primer auto\n";
        cout << "4. Convertir lista\n";
        cout << "5. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                lista.insertar();
                break;

            case 2:
                lista.mostrar();
                break;

            case 3:
                lista.eliminarInicio();
                break;

            case 4:
                lista.convertir();
                break;

            case 5:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 5);

    return 0;
}