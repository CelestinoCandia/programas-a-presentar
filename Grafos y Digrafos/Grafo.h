#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>
#include "Conexion.h"

using namespace std;

class GrafoBase {
protected:
    vector<int> nodos;
    vector<Conexion> rutas;

    bool esDirigido;
    string archivoDatos;      // datos_grafo.json o datos_digrafo.json -> SOLO nodos y rutas
    string archivoResultados; // resultados_grafo.json o resultados_digrafo.json -> SOLO Dijkstra

    // Guardan el ultimo resultado calculado de Dijkstra, para poder exportarlo
    vector<int>  ultDistancias;
    vector<bool> ultAlcanzable;
    int     ultOrigen;
    bool    ultPorCosto;
    bool    hayResultadoDijkstra;

public:

    GrafoBase(bool dirigido);
    void agregarNodo(int id);
    void agregarRuta(int inicio, int fin, string nombreArista, int tiempo, int costo);
    void mostrarRutas();
    void calcularDijkstra(int origen, bool porCosto);
    void enumerarTodasLasRutas(int origen, int destino, bool porCosto);
    bool nodoExiste(int id);
    int  maxNodoId();

    // Exportacion de resultados (resultados de Dijkstra, snapshot de solo lectura)
    void generarTXT();
    void generarJSON();
    void generarCSV();
    void generarXML();
    void generarTodos();

    // Persistencia: el archivo JSON es la fuente de verdad de nodos/rutas
    void cargarDesdeArchivo();
    void guardarEnArchivo();
};

// CLASE HIJA 1: Grafo No Dirigido
class GrafoNoDirigido : public GrafoBase {
public:
    GrafoNoDirigido() : GrafoBase(false) {}
};

// CLASE HIJA 2: Digrafo Dirigido
class DigrafoDirigido : public GrafoBase {
public:
    DigrafoDirigido() : GrafoBase(true) {}
};

#endif
