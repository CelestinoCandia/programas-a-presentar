#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <fstream>
#include "Nodo.h"
using namespace std;

class Lista {
private:
    Nodo* inicio;

public:
    Lista() {
        inicio = NULL;
    }

    void insertar() {
        Nodo* nuevo = new Nodo();
        nuevo->dato.capturar();

        if (inicio == NULL) {
            inicio = nuevo;
        } else {
            Nodo* aux = inicio;

            while (aux->siguiente != NULL) {
                aux = aux->siguiente;
            }

            aux->siguiente = nuevo;
        }

        cout << "Auto agregado correctamente.\n";
    }

    void mostrar() {
        if (inicio == NULL) {
            cout << "La lista esta vacia.\n";
            return;
        }

        Nodo* aux = inicio;
        int contador = 1;

        while (aux != NULL) {
            cout << "\nAuto #" << contador << endl;
            aux->dato.mostrar();
            aux = aux->siguiente;
            contador++;
        }
    }

    void eliminarInicio() {
        if (inicio == NULL) {
            cout << "La lista esta vacia.\n";
            return;
        }

        Nodo* aux = inicio;
        inicio = inicio->siguiente;
        delete aux;

        cout << "Primer auto eliminado correctamente.\n";
    }

    void convertirTXT() {
        ofstream archivo("autos.txt");

        Nodo* aux = inicio;

        while (aux != NULL) {
            archivo << "Marca: " << aux->dato.getMarca() << endl;
            archivo << "Precio: " << aux->dato.getPrecio() << endl;
            archivo << "Anio: " << aux->dato.getAnio() << endl;
            archivo << "------------------------" << endl;

            aux = aux->siguiente;
        }

        archivo.close();
        cout << "Archivo autos.txt creado correctamente.\n";
    }

    void convertirXML() {
        ofstream archivo("autos.xml");

        archivo << "<autos>" << endl;

        Nodo* aux = inicio;

        while (aux != NULL) {
            archivo << "  <auto>" << endl;
            archivo << "    <marca>" << aux->dato.getMarca() << "</marca>" << endl;
            archivo << "    <precio>" << aux->dato.getPrecio() << "</precio>" << endl;
            archivo << "    <anio>" << aux->dato.getAnio() << "</anio>" << endl;
            archivo << "  </auto>" << endl;

            aux = aux->siguiente;
        }

        archivo << "</autos>" << endl;

        archivo.close();
        cout << "Archivo autos.xml creado correctamente.\n";
    }

    void convertirHTML() {
        ofstream archivo("autos.html");

        archivo << "<html>" << endl;
        archivo << "<head><title>Autos</title></head>" << endl;
        archivo << "<body>" << endl;
        archivo << "<h1>Lista de Autos</h1>" << endl;
        archivo << "<table border='1'>" << endl;
        archivo << "<tr><th>Marca</th><th>Precio</th><th>Anio</th></tr>" << endl;

        Nodo* aux = inicio;

        while (aux != NULL) {
            archivo << "<tr>";
            archivo << "<td>" << aux->dato.getMarca() << "</td>";
            archivo << "<td>" << aux->dato.getPrecio() << "</td>";
            archivo << "<td>" << aux->dato.getAnio() << "</td>";
            archivo << "</tr>" << endl;

            aux = aux->siguiente;
        }

        archivo << "</table>" << endl;
        archivo << "</body>" << endl;
        archivo << "</html>" << endl;

        archivo.close();
        cout << "Archivo autos.html creado correctamente.\n";
    }

    void convertirJSON() {
        ofstream archivo("autos.json");

        archivo << "[" << endl;

        Nodo* aux = inicio;

        while (aux != NULL) {
            archivo << "  {" << endl;
            archivo << "    \"marca\": \"" << aux->dato.getMarca() << "\"," << endl;
            archivo << "    \"precio\": " << aux->dato.getPrecio() << "," << endl;
            archivo << "    \"anio\": " << aux->dato.getAnio() << endl;
            archivo << "  }";

            if (aux->siguiente != NULL) {
                archivo << ",";
            }

            archivo << endl;

            aux = aux->siguiente;
        }

        archivo << "]" << endl;

        archivo.close();
        cout << "Archivo autos.json creado correctamente.\n";
    }

    void convertir() {
        int opcion;

        if (inicio == NULL) {
            cout << "No hay autos para convertir.\n";
            return;
        }

        cout << "\n===== CONVERSOR =====\n";
        cout << "1. Convertir a TXT\n";
        cout << "2. Convertir a XML\n";
        cout << "3. Convertir a HTML\n";
        cout << "4. Convertir a JSON\n";
        cout << "Elige el formato: ";
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

    ~Lista() {
        Nodo* aux;

        while (inicio != NULL) {
            aux = inicio;
            inicio = inicio->siguiente;
            delete aux;
        }
    }
};

#endif