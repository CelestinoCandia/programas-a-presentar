#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <map>
#include <tuple>
#include "Grafo.h"

using namespace std;

GrafoBase::GrafoBase(bool dirigido) {
    esDirigido = dirigido;
    hayResultadoDijkstra = false;
    ultOrigen = -1;
    ultPorCosto = false;
    archivoDatos = dirigido ? "datos_digrafo.json" : "datos_grafo.json";
    archivoResultados = dirigido ? "resultados_digrafo.json" : "resultados_grafo.json";
    cargarDesdeArchivo();
}

bool GrafoBase::nodoExiste(int id) {
    for (size_t i = 0; i < nodos.size(); i++) {
        if (nodos[i] == id) return true;
    }
    return false;
}

int GrafoBase::maxNodoId() {
    int maxId = -1;
    for (size_t i = 0; i < nodos.size(); i++) {
        if (nodos[i] > maxId) maxId = nodos[i];
    }
    return maxId;
}

void GrafoBase::agregarNodo(int id) {
    if (!nodoExiste(id)) {
        nodos.push_back(id);
    }
}

void GrafoBase::agregarRuta(int inicio, int fin, string nombreArista, int t, int c) {
    agregarNodo(inicio);
    agregarNodo(fin);

    Conexion nueva;
    nueva.nodoInicial = inicio;
    nueva.nodoFinal = fin;
    nueva.aristaConexion = nombreArista;
    nueva.tiempo = t;
    nueva.costo = c;
    rutas.push_back(nueva);

    
    guardarEnArchivo();
}

void GrafoBase::mostrarRutas() {
    
    cargarDesdeArchivo();

    if (rutas.empty()) {
        cout << "No hay conexiones registradas.\n";
        return;
    }
    for (size_t i = 0; i < rutas.size(); i++) {
        cout << "Ruta [" << rutas[i].aristaConexion << "]: Nodo "
             << rutas[i].nodoInicial << " -> Nodo " << rutas[i].nodoFinal
             << " | Tiempo: " << rutas[i].tiempo << " min | Costo: $" << rutas[i].costo << "\n";
    }
}

void GrafoBase::calcularDijkstra(int origen, bool porCosto) {
    
    cargarDesdeArchivo();

    if (!nodoExiste(origen)) {
        cout << "El nodo origen no existe en el mapa.\n";
        return;
    }

    
    int m = (int)nodos.size();
    map<int, int> idAIndice;
    for (int i = 0; i < m; i++) {
        idAIndice[nodos[i]] = i;
    }

    vector<vector<int>> adj(m, vector<int>(m, INT_MAX));
    for (int i = 0; i < m; i++) adj[i][i] = 0;

    for (size_t i = 0; i < rutas.size(); i++) {
        int u = idAIndice[rutas[i].nodoInicial];
        int v = idAIndice[rutas[i].nodoFinal];
        int peso = porCosto ? rutas[i].costo : rutas[i].tiempo;

        if (peso < adj[u][v]) adj[u][v] = peso;
        if (!esDirigido) {
            if (peso < adj[v][u]) adj[v][u] = peso;
        }
    }

    vector<int> dist(m, INT_MAX);
    vector<bool> visitado(m, false);
    int origenIdx = idAIndice[origen];
    dist[origenIdx] = 0;

    for (int count = 0; count < m - 1; count++) {
        int minimo = INT_MAX, u = -1;

        for (int v = 0; v < m; v++) {
            if (!visitado[v] && dist[v] <= minimo) {
                minimo = dist[v];
                u = v;
            }
        }

        if (u == -1) break;
        visitado[u] = true;

        for (int v = 0; v < m; v++) {
            if (!visitado[v] && adj[u][v] != INT_MAX
                && dist[u] != INT_MAX && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
            }
        }
    }

    cout << "\n=== RESULTADOS DE DIJKSTRA ===\n";
    cout << "Nodo Origen: " << origen
         << (porCosto ? " | Criterio: Costo ($)\n" : " | Criterio: Tiempo (min)\n");

    
    int maxId = maxNodoId();
    int tam = (maxId < 0) ? 1 : maxId + 1;

    ultOrigen = origen;
    ultPorCosto = porCosto;
    hayResultadoDijkstra = true;
    ultDistancias.assign(tam, 0);
    ultAlcanzable.assign(tam, false);

    for (int i = 0; i < m; i++) {
        int idReal = nodos[i];
        ultDistancias[idReal] = (dist[i] == INT_MAX) ? 0 : dist[i];
        ultAlcanzable[idReal] = (dist[i] != INT_MAX);
    }

    
    bool hayDestinos = false;
    int  idMasCercano = -1, distMasCercano = INT_MAX;
    int  idMasLejano  = -1, distMasLejano  = -1;

    for (int i = 0; i < m; i++) {
        int idReal = nodos[i];
        cout << "  Nodo Origen " << origen << " -> Nodo Destino " << idReal << " : ";
        if (dist[i] == INT_MAX) {
            cout << "Inalcanzable\n";
            continue;
        }

        cout << dist[i] << (porCosto ? " pesos" : " min") << "\n";

        if (idReal == origen) continue; // no comparamos el origen contra si mismo

        hayDestinos = true;
        if (dist[i] < distMasCercano) {
            distMasCercano = dist[i];
            idMasCercano = idReal;
        }
        if (dist[i] > distMasLejano) {
            distMasLejano = dist[i];
            idMasLejano = idReal;
        }
    }

    cout << "\n--- RESUMEN ---\n";
    if (!hayDestinos) {
        cout << "  No hay otros nodos alcanzables desde el Nodo Origen " << origen << ".\n";
    } else {
        cout << "  Ruta MAS CORTA  : Nodo Origen " << origen << " -> Nodo Destino "
             << idMasCercano << " (" << distMasCercano << (porCosto ? " pesos" : " min") << ")\n";
        cout << "  Ruta MAS LARGA  : Nodo Origen " << origen << " -> Nodo Destino "
             << idMasLejano  << " (" << distMasLejano  << (porCosto ? " pesos" : " min") << ")\n";
    }
}



static void buscarCaminosDFS(
    int actual,
    int destino,
    map<int, vector<tuple<int,int,string>>>& adyacencia,
    vector<bool>& visitado,
    vector<int>& caminoActual,
    vector<int>& pesoActual,        // peso de la arista usada para llegar a cada nodo del camino
    vector<string>& aristaActual,   // nombre de la arista usada para llegar a cada nodo del camino
    vector<vector<int>>& todosLosCaminos,
    vector<int>& todosLosPesosTotales,
    vector<vector<int>>& todosLosPesosPorTramo,
    vector<vector<string>>& todosLosNombresPorTramo)
{
    visitado[actual] = true;
    caminoActual.push_back(actual);

    if (actual == destino) {
        
        todosLosCaminos.push_back(caminoActual);
        todosLosPesosPorTramo.push_back(pesoActual);
        todosLosNombresPorTramo.push_back(aristaActual);

        int total = 0;
        for (size_t i = 0; i < pesoActual.size(); i++) total += pesoActual[i];
        todosLosPesosTotales.push_back(total);
    } else {
        for (size_t i = 0; i < adyacencia[actual].size(); i++) {
            int vecino  = get<0>(adyacencia[actual][i]);
            int peso    = get<1>(adyacencia[actual][i]);
            string arista = get<2>(adyacencia[actual][i]);

            if (!visitado[vecino]) {
                pesoActual.push_back(peso);
                aristaActual.push_back(arista);

                buscarCaminosDFS(vecino, destino, adyacencia, visitado, caminoActual,
                                  pesoActual, aristaActual, todosLosCaminos,
                                  todosLosPesosTotales, todosLosPesosPorTramo,
                                  todosLosNombresPorTramo);

                pesoActual.pop_back();
                aristaActual.pop_back();
            }
        }
    }

    
    visitado[actual] = false;
    caminoActual.pop_back();
}

void GrafoBase::enumerarTodasLasRutas(int origen, int destino, bool porCosto) {
    cargarDesdeArchivo();

    if (!nodoExiste(origen)) {
        cout << "El nodo origen " << origen << " no existe en el mapa.\n";
        return;
    }
    if (!nodoExiste(destino)) {
        cout << "El nodo destino " << destino << " no existe en el mapa.\n";
        return;
    }

    
    map<int, vector<tuple<int,int,string>>> adyacencia;
    for (size_t i = 0; i < rutas.size(); i++) {
        int u = rutas[i].nodoInicial;
        int v = rutas[i].nodoFinal;
        int peso = porCosto ? rutas[i].costo : rutas[i].tiempo;

        adyacencia[u].push_back(make_tuple(v, peso, rutas[i].aristaConexion));
        if (!esDirigido) {
            adyacencia[v].push_back(make_tuple(u, peso, rutas[i].aristaConexion));
        }
    }

    int maxId = maxNodoId();
    int tam = (maxId < 0) ? 1 : maxId + 1;
    vector<bool> visitado(tam, false);

    vector<int> caminoActual;
    vector<int> pesoActual;
    vector<string> aristaActual;

    vector<vector<int>> todosLosCaminos;
    vector<int> todosLosPesosTotales;
    vector<vector<int>> todosLosPesosPorTramo;
    vector<vector<string>> todosLosNombresPorTramo;

    buscarCaminosDFS(origen, destino, adyacencia, visitado, caminoActual,
                      pesoActual, aristaActual, todosLosCaminos,
                      todosLosPesosTotales, todosLosPesosPorTramo,
                      todosLosNombresPorTramo);

    cout << "\n=== TODAS LAS RUTAS POSIBLES ===\n";
    cout << "Nodo Origen: " << origen << "  |  Nodo Destino: " << destino
         << (porCosto ? "  |  Criterio: Costo ($)\n" : "  |  Criterio: Tiempo (min)\n");

    if (todosLosCaminos.empty()) {
        cout << "No existe ningun camino entre el Nodo Origen " << origen
             << " y el Nodo Destino " << destino << ".\n";
        return;
    }

    for (size_t r = 0; r < todosLosCaminos.size(); r++) {
        cout << "\nRuta " << (r + 1) << ": ";
        for (size_t i = 0; i < todosLosCaminos[r].size(); i++) {
            cout << "Nodo " << todosLosCaminos[r][i];
            if (i + 1 < todosLosCaminos[r].size()) {
                cout << " --[" << todosLosNombresPorTramo[r][i]
                     << ", " << todosLosPesosPorTramo[r][i]
                     << (porCosto ? " pesos" : " min") << "]--> ";
            }
        }
        cout << "\n  Total: " << todosLosPesosTotales[r] << (porCosto ? " pesos" : " min") << "\n";
    }

    
    int idxMasCorta = 0, idxMasLarga = 0;
    for (size_t r = 1; r < todosLosPesosTotales.size(); r++) {
        if (todosLosPesosTotales[r] < todosLosPesosTotales[idxMasCorta]) idxMasCorta = (int)r;
        if (todosLosPesosTotales[r] > todosLosPesosTotales[idxMasLarga]) idxMasLarga = (int)r;
    }

    cout << "\n--- RESUMEN ---\n";
    cout << "Se encontraron " << todosLosCaminos.size() << " ruta(s) entre el Nodo Origen "
         << origen << " y el Nodo Destino " << destino << ".\n";
    cout << "  Ruta MAS CORTA : Ruta " << (idxMasCorta + 1) << " con "
         << todosLosPesosTotales[idxMasCorta] << (porCosto ? " pesos" : " min") << "\n";
    cout << "  Ruta MAS LARGA : Ruta " << (idxMasLarga + 1) << " con "
         << todosLosPesosTotales[idxMasLarga] << (porCosto ? " pesos" : " min") << "\n";
}




void GrafoBase::guardarEnArchivo() {
    ofstream archivo(archivoDatos);

    archivo << "{\n";
    archivo << "  \"tipoGrafo\": \"" << (esDirigido ? "Digrafo" : "Grafo") << "\",\n";

    archivo << "  \"nodos\": [";
    for (size_t i = 0; i < nodos.size(); i++) {
        archivo << nodos[i];
        if (i + 1 < nodos.size()) archivo << ", ";
    }
    archivo << "],\n";

    archivo << "  \"rutas\": [\n";
    for (size_t i = 0; i < rutas.size(); i++) {
        archivo << "    {\n";
        archivo << "      \"arista\": \"" << rutas[i].aristaConexion << "\",\n";
        archivo << "      \"nodoInicial\": " << rutas[i].nodoInicial << ",\n";
        archivo << "      \"nodoFinal\": " << rutas[i].nodoFinal << ",\n";
        archivo << "      \"tiempo\": " << rutas[i].tiempo << ",\n";
        archivo << "      \"costo\": " << rutas[i].costo << "\n";
        archivo << "    }" << (i + 1 < rutas.size() ? "," : "") << "\n";
    }
    archivo << "  ]\n";
    archivo << "}\n";

    archivo.close();
}


static string extraerValorString(const string& bloque, const string& clave) {
    string buscar = "\"" + clave + "\"";
    size_t pos = bloque.find(buscar);
    if (pos == string::npos) return "";
    pos = bloque.find(':', pos);
    if (pos == string::npos) return "";
    size_t inicioComillas = bloque.find('"', pos + 1);
    if (inicioComillas == string::npos) return "";
    size_t finComillas = bloque.find('"', inicioComillas + 1);
    if (finComillas == string::npos) return "";
    return bloque.substr(inicioComillas + 1, finComillas - inicioComillas - 1);
}

static int extraerValorInt(const string& bloque, const string& clave) {
    string buscar = "\"" + clave + "\"";
    size_t pos = bloque.find(buscar);
    if (pos == string::npos) return 0;
    pos = bloque.find(':', pos);
    if (pos == string::npos) return 0;
    pos++;
    while (pos < bloque.size() && (bloque[pos] == ' ' || bloque[pos] == '\n')) pos++;
    size_t fin = pos;
    while (fin < bloque.size() && (isdigit((unsigned char)bloque[fin]) || bloque[fin] == '-')) fin++;
    if (fin == pos) return 0;
    return atoi(bloque.substr(pos, fin - pos).c_str());
}

void GrafoBase::cargarDesdeArchivo() {
    ifstream archivo(archivoDatos);
    if (!archivo.is_open()) {
        // Primera vez que se usa este tipo de grafo, no hay archivo todavia.
        nodos.clear();
        rutas.clear();
        return;
    }

    stringstream ss;
    ss << archivo.rdbuf();
    string contenido = ss.str();
    archivo.close();

    nodos.clear();
    rutas.clear();

    // --- nodos: [1, 2, 3, ...] ---
    size_t posNodos = contenido.find("\"nodos\"");
    if (posNodos != string::npos) {
        size_t inicio = contenido.find('[', posNodos);
        size_t fin = contenido.find(']', inicio);
        if (inicio != string::npos && fin != string::npos) {
            string listaNodos = contenido.substr(inicio + 1, fin - inicio - 1);
            stringstream lista(listaNodos);
            string item;
            while (getline(lista, item, ',')) {
                // limpiar espacios
                size_t a = item.find_first_not_of(" \n\t");
                size_t b = item.find_last_not_of(" \n\t");
                if (a != string::npos) {
                    string limpio = item.substr(a, b - a + 1);
                    if (!limpio.empty()) nodos.push_back(atoi(limpio.c_str()));
                }
            }
        }
    }

    // --- rutas: [ { ... }, { ... } ] ---
    size_t posRutas = contenido.find("\"rutas\"");
    if (posRutas != string::npos) {
        size_t cursor = contenido.find('[', posRutas);
        size_t finArreglo = contenido.find(']', cursor);
        while (cursor != string::npos && cursor < finArreglo) {
            size_t abre = contenido.find('{', cursor);
            if (abre == string::npos || abre > finArreglo) break;
            size_t cierra = contenido.find('}', abre);
            if (cierra == string::npos) break;

            string bloque = contenido.substr(abre, cierra - abre + 1);

            Conexion c;
            c.aristaConexion = extraerValorString(bloque, "arista");
            c.nodoInicial = extraerValorInt(bloque, "nodoInicial");
            c.nodoFinal = extraerValorInt(bloque, "nodoFinal");
            c.tiempo = extraerValorInt(bloque, "tiempo");
            c.costo = extraerValorInt(bloque, "costo");
            rutas.push_back(c);

            // asegurar que los nodos referenciados existan en la lista de nodos
            agregarNodo(c.nodoInicial);
            agregarNodo(c.nodoFinal);

            cursor = cierra + 1;
        }
    }
}




void GrafoBase::generarTXT() {
    cargarDesdeArchivo();
    ofstream archivo("resultados.txt");

    archivo << "TIPO DE GRAFO: " << (esDirigido ? "Digrafo (Dirigido)" : "Grafo (No Dirigido)") << "\n\n";

    archivo << "NODOS REGISTRADOS (" << nodos.size() << ")\n";
    for (size_t i = 0; i < nodos.size(); i++) {
        archivo << "  - Nodo " << nodos[i] << "\n";
    }

    archivo << "\nRUTAS / CONEXIONES (" << rutas.size() << ")\n";
    for (size_t i = 0; i < rutas.size(); i++) {
        archivo << "  - [" << rutas[i].aristaConexion << "] Nodo " << rutas[i].nodoInicial
                << " -> Nodo " << rutas[i].nodoFinal
                << " | Tiempo: " << rutas[i].tiempo << " min"
                << " | Costo: $" << rutas[i].costo << "\n";
    }

    archivo << "\nRESULTADOS DIJKSTRA\n";
    if (!hayResultadoDijkstra) {
        archivo << "  No se ha calculado ninguna ruta optima todavia.\n";
    } else {
        archivo << "  Nodo origen: " << ultOrigen << "\n";
        archivo << "  Optimizado por: " << (ultPorCosto ? "Costo" : "Tiempo") << "\n";
        for (size_t i = 0; i < ultDistancias.size(); i++) {
            if (nodoExiste((int)i)) {
                archivo << "  - Hacia Nodo " << i << " -> ";
                if (!ultAlcanzable[i]) archivo << "Inalcanzable\n";
                else archivo << ultDistancias[i] << (ultPorCosto ? " pesos\n" : " min\n");
            }
        }
    }

    archivo.close();
    cout << "resultados.txt generado\n";
}

void GrafoBase::generarJSON() {
    
    cargarDesdeArchivo();
    ofstream archivo(archivoResultados);

    archivo << "{\n";
    archivo << "  \"tipoGrafo\": \"" << (esDirigido ? "Digrafo" : "Grafo") << "\",\n";
    archivo << "  \"dijkstra\": ";

    if (!hayResultadoDijkstra) {
        archivo << "null\n";
    } else {
        archivo << "{\n";
        archivo << "    \"origen\": " << ultOrigen << ",\n";
        archivo << "    \"optimizadoPor\": \"" << (ultPorCosto ? "costo" : "tiempo") << "\",\n";
        archivo << "    \"distancias\": [\n";
        bool primero = true;
        for (size_t i = 0; i < ultDistancias.size(); i++) {
            if (nodoExiste((int)i)) {
                if (!primero) archivo << ",\n";
                archivo << "      {\"nodo\": " << i << ", \"alcanzable\": "
                        << (ultAlcanzable[i] ? "true" : "false") << ", \"distancia\": "
                        << (ultAlcanzable[i] ? ultDistancias[i] : 0) << "}";
                primero = false;
            }
        }
        archivo << "\n    ]\n";
        archivo << "  }\n";
    }

    archivo << "}\n";
    archivo.close();

    if (!hayResultadoDijkstra) {
        cout << archivoResultados << " generado (sin resultado de Dijkstra todavia)\n";
    } else {
        cout << archivoResultados << " generado con el ultimo resultado de Dijkstra\n";
    }
}

void GrafoBase::generarCSV() {
    cargarDesdeArchivo();
    ofstream archivo("resultados.csv");

    archivo << "seccion,nodoInicial,nodoFinal,arista,tiempo,costo,alcanzable\n";

    for (size_t i = 0; i < nodos.size(); i++) {
        archivo << "nodo," << nodos[i] << ",,,,,\n";
    }

    for (size_t i = 0; i < rutas.size(); i++) {
        archivo << "ruta," << rutas[i].nodoInicial << "," << rutas[i].nodoFinal << ","
                << rutas[i].aristaConexion << "," << rutas[i].tiempo << ","
                << rutas[i].costo << ",\n";
    }

    if (hayResultadoDijkstra) {
        for (size_t i = 0; i < ultDistancias.size(); i++) {
            if (nodoExiste((int)i)) {
                archivo << "dijkstra(" << (ultPorCosto ? "costo" : "tiempo") << " desde " << ultOrigen << "),"
                        << ultOrigen << "," << i << ",,";
                if (ultAlcanzable[i]) archivo << ultDistancias[i];
                archivo << ",";
                archivo << (ultAlcanzable[i] ? "si" : "no") << "\n";
            }
        }
    }

    archivo.close();
    cout << "resultados.csv generado\n";
}

void GrafoBase::generarXML() {
    cargarDesdeArchivo();
    ofstream archivo("resultados.xml");

    archivo << "<grafo tipo=\"" << (esDirigido ? "digrafo" : "no_dirigido") << "\">\n";

    archivo << "  <nodos>\n";
    for (size_t i = 0; i < nodos.size(); i++) {
        archivo << "    <nodo id=\"" << nodos[i] << "\"/>\n";
    }
    archivo << "  </nodos>\n";

    archivo << "  <rutas>\n";
    for (size_t i = 0; i < rutas.size(); i++) {
        archivo << "    <ruta arista=\"" << rutas[i].aristaConexion << "\" "
                << "nodoInicial=\"" << rutas[i].nodoInicial << "\" "
                << "nodoFinal=\"" << rutas[i].nodoFinal << "\" "
                << "tiempo=\"" << rutas[i].tiempo << "\" "
                << "costo=\"" << rutas[i].costo << "\"/>\n";
    }
    archivo << "  </rutas>\n";

    archivo << "  <dijkstra";
    if (!hayResultadoDijkstra) {
        archivo << " calculado=\"false\"/>\n";
    } else {
        archivo << " calculado=\"true\" origen=\"" << ultOrigen << "\" optimizadoPor=\""
                << (ultPorCosto ? "costo" : "tiempo") << "\">\n";
        for (size_t i = 0; i < ultDistancias.size(); i++) {
            if (nodoExiste((int)i)) {
                archivo << "    <destino nodo=\"" << i << "\" alcanzable=\""
                        << (ultAlcanzable[i] ? "true" : "false") << "\"";
                if (ultAlcanzable[i]) archivo << " distancia=\"" << ultDistancias[i] << "\"";
                archivo << "/>\n";
            }
        }
        archivo << "  </dijkstra>\n";
    }

    archivo << "</grafo>\n";
    archivo.close();
    cout << "resultados.xml generado\n";
}

void GrafoBase::generarTodos() {
    generarTXT();
    generarJSON();
    generarCSV();
    generarXML();
    cout << "Todos los archivos generados!\n";
}
