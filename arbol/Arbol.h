#ifndef ARBOL_H
#define ARBOL_H

#include <iostream>
#include <fstream>
#include "NodoArbol.h"
using namespace std;

class Arbol {
private:
    NodoArbol* raiz;

    void insertarRec(NodoArbol*& nodo, Auto autoNuevo) {
        if (nodo == NULL) {
            nodo = new NodoArbol();
            nodo->dato = autoNuevo;
        } else if (autoNuevo.getAnio() < nodo->dato.getAnio()) {
            insertarRec(nodo->izquierda, autoNuevo);
        } else {
            insertarRec(nodo->derecha, autoNuevo);
        }
    }

    void inOrdenRec(NodoArbol* nodo) {
        if (nodo != NULL) {
            inOrdenRec(nodo->izquierda);
            nodo->dato.mostrar();
            cout << "------------------" << endl;
            inOrdenRec(nodo->derecha);
        }
    }

    void guardarTXTRec(NodoArbol* nodo, ofstream& archivo) {
        if (nodo != NULL) {
            guardarTXTRec(nodo->izquierda, archivo);

            archivo << "Marca: " << nodo->dato.getMarca() << endl;
            archivo << "Precio: " << nodo->dato.getPrecio() << endl;
            archivo << "Anio: " << nodo->dato.getAnio() << endl;
            archivo << "------------------" << endl;

            guardarTXTRec(nodo->derecha, archivo);
        }
    }

    void guardarXMLRec(NodoArbol* nodo, ofstream& archivo) {
        if (nodo != NULL) {
            guardarXMLRec(nodo->izquierda, archivo);

            archivo << "  <auto>" << endl;
            archivo << "    <marca>" << nodo->dato.getMarca() << "</marca>" << endl;
            archivo << "    <precio>" << nodo->dato.getPrecio() << "</precio>" << endl;
            archivo << "    <anio>" << nodo->dato.getAnio() << "</anio>" << endl;
            archivo << "  </auto>" << endl;

            guardarXMLRec(nodo->derecha, archivo);
        }
    }

    void guardarHTMLRec(NodoArbol* nodo, ofstream& archivo) {
        if (nodo != NULL) {
            guardarHTMLRec(nodo->izquierda, archivo);

            archivo << "<tr>";
            archivo << "<td>" << nodo->dato.getMarca() << "</td>";
            archivo << "<td>" << nodo->dato.getPrecio() << "</td>";
            archivo << "<td>" << nodo->dato.getAnio() << "</td>";
            archivo << "</tr>" << endl;

            guardarHTMLRec(nodo->derecha, archivo);
        }
    }

    void guardarJSONRec(NodoArbol* nodo, ofstream& archivo, bool& primero) {
        if (nodo != NULL) {
            guardarJSONRec(nodo->izquierda, archivo, primero);

            if (!primero) {
                archivo << "," << endl;
            }

            archivo << "  {" << endl;
            archivo << "    \"marca\": \"" << nodo->dato.getMarca() << "\"," << endl;
            archivo << "    \"precio\": " << nodo->dato.getPrecio() << "," << endl;
            archivo << "    \"anio\": " << nodo->dato.getAnio() << endl;
            archivo << "  }";

            primero = false;

            guardarJSONRec(nodo->derecha, archivo, primero);
        }
    }

    void liberarRec(NodoArbol* nodo) {
        if (nodo != NULL) {
            liberarRec(nodo->izquierda);
            liberarRec(nodo->derecha);
            delete nodo;
        }
    }

public:
    Arbol() {
        raiz = NULL;
    }

    void insertar() {
        Auto nuevo;
        nuevo.capturar();
        insertarRec(raiz, nuevo);
        cout << "Auto insertado en el arbol correctamente.\n";
    }

    void mostrarInOrden() {
        if (raiz == NULL) {
            cout << "El arbol esta vacio.\n";
        } else {
            cout << "\n AUTOS EN INORDEN \n";
            inOrdenRec(raiz);
        }
    }

    void convertirTXT() {
        ofstream archivo("autos_arbol.txt");
        guardarTXTRec(raiz, archivo);
        archivo.close();
        cout << "Archivo autos_arbol.txt creado correctamente.\n";
    }

    void convertirXML() {
        ofstream archivo("autos_arbol.xml");

        archivo << "<autos>" << endl;
        guardarXMLRec(raiz, archivo);
        archivo << "</autos>" << endl;

        archivo.close();
        cout << "Archivo autos_arbol.xml creado correctamente.\n";
    }

    void convertirHTML() {
        ofstream archivo("autos_arbol.html");

        archivo << "<html>" << endl;
        archivo << "<head><title>Autos Arbol</title></head>" << endl;
        archivo << "<body>" << endl;
        archivo << "<h1>Autos del Arbol</h1>" << endl;
        archivo << "<table border='1'>" << endl;
        archivo << "<tr><th>Marca</th><th>Precio</th><th>Anio</th></tr>" << endl;

        guardarHTMLRec(raiz, archivo);

        archivo << "</table>" << endl;
        archivo << "</body>" << endl;
        archivo << "</html>" << endl;

        archivo.close();
        cout << "Archivo autos_arbol.html creado correctamente.\n";
    }

    void convertirJSON() {
        ofstream archivo("autos_arbol.json");
        bool primero = true;

        archivo << "[" << endl;
        guardarJSONRec(raiz, archivo, primero);
        archivo << endl << "]" << endl;

        archivo.close();
        cout << "Archivo autos_arbol.json creado correctamente.\n";
    }

    void convertir() {
        int opcion;

        if (raiz == NULL) {
            cout << "No hay autos para convertir.\n";
            return;
        }

        cout << "\n CONVERSOR DEL ARBOL \n";
        cout << "1. Convertir a TXT\n";
        cout << "2. Convertir a XML\n";
        cout << "3. Convertir a HTML\n";
        cout << "4. Convertir a JSON\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                convertirTXT();
                break;
            case 2:
                convertirXML();
                break;
            case 3:
                convertirHTML();
                break;
            case 4:
                convertirJSON();
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    }

    ~Arbol() {
        liberarRec(raiz);
    }
};

#endif