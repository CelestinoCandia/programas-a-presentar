#include <iostream>
#include <string>
#include "Grafo.h"

using namespace std;

void ejecutarSimulacion(GrafoBase* mapa) {
    int opcion;

    do {
        
        mapa->cargarDesdeArchivo();

        cout << "\n--- MENU DE LOGISTICA Y RUTAS ---\n";
        cout << "1. Registrar nueva conexion (Ruta)\n";
        cout << "2. Mostrar mapa de conexiones\n";
        cout << "3. Calcular ruta mas rapida (Dijkstra por Tiempo)\n";
        cout << "4. Calcular ruta mas barata (Dijkstra por Costo)\n";
        cout << "5. Ver TODAS las rutas posibles entre dos nodos\n";
        cout << "6. Exportar resultados (TXT/JSON/CSV/XML)\n";
        cout << "7. Regresar al menu principal\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int ini, fin, t, c; string nombre;
                cout << "Nodo Inicial (ID entero): "; cin >> ini;
                cout << "Nodo Final (ID entero): "; cin >> fin;
                cout << "Nombre de la Arista: "; cin >> nombre;
                cout << "Tiempo de traslado (minutos): "; cin >> t;
                cout << "Costo de traslado (pesos): "; cin >> c;
                mapa->agregarRuta(ini, fin, nombre, t, c);
                cout << "Ruta agregada y guardada.\n";
                break;
            }
            case 2:
                cout << "\n--- CONJUNTOS DE CONEXIONES REGISTRADAS ---\n";
                mapa->mostrarRutas();
                break;
            case 3: {
                int orig;
                cout << "Ingresa el ID del nodo origen: "; cin >> orig;
                mapa->calcularDijkstra(orig, false);
                break;
            }
            case 4: {
                int orig;
                cout << "Ingresa el ID del nodo origen: "; cin >> orig;
                mapa->calcularDijkstra(orig, true);
                break;
            }
            case 5: {
                int orig, dest, criterio;
                cout << "Ingresa el ID del nodo origen: "; cin >> orig;
                cout << "Ingresa el ID del nodo destino: "; cin >> dest;
                cout << "Calcular por:\n  1. Tiempo (min)\n  2. Costo (pesos)\n";
                cout << "Opcion: "; cin >> criterio;
                mapa->enumerarTodasLasRutas(orig, dest, criterio == 2);
                break;
            }
            case 6: {
                int opExport;
                do {
                    cout << "\n--- EXPORTAR RESULTADOS ---\n";
                    cout << "1. TXT\n";
                    cout << "2. JSON (sincroniza con el archivo de datos)\n";
                    cout << "3. CSV\n";
                    cout << "4. XML\n";
                    cout << "5. Todos\n";
                    cout << "0. Regresar\n";
                    cout << "Opcion: ";
                    cin >> opExport;

                    switch (opExport) {
                        case 1: mapa->generarTXT();  break;
                        case 2: mapa->generarJSON(); break;
                        case 3: mapa->generarCSV();  break;
                        case 4: mapa->generarXML();  break;
                        case 5: mapa->generarTodos(); break;
                        case 0: break;
                        default: cout << "Opcion invalida.\n";
                    }
                } while (opExport != 0);
                break;
            }
            default:
                if (opcion != 7) cout << "Opcion invalida.\n";
        }
    } while (opcion != 7);
}

int main() {
    int tipoGrafo;
    do {
        cout << "1. GRAFO \n";
        cout << "2. DIGRAFO \n";
        cout << "3. Finalizar\n";
        cout << "Elige una opcion: ";
        cin >> tipoGrafo;

        if (tipoGrafo == 1) {
            cout << "\n[Cargando estructura de Grafo No Dirigido...]\n";
            cout << "[Se cargaron los datos guardados en datos_grafo.json, si existian]\n";
            GrafoNoDirigido miGrafo;
            ejecutarSimulacion(&miGrafo);
        } else if (tipoGrafo == 2) {
            cout << "\n[Cargando estructura de Digrafo Dirigido...]\n";
            cout << "[Se cargaron los datos guardados en datos_digrafo.json, si existian]\n";
            DigrafoDirigido miDigrafo;
            ejecutarSimulacion(&miDigrafo);
        }
    } while (tipoGrafo != 3);

    return 0;
}
