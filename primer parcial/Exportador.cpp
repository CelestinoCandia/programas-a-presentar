#include "Exportador.h"
#include "Historial.h"
#include <iostream>
#include <fstream>
using namespace std;

void generarTXT() {
    ofstream archivo("datos.txt");

    archivo << "\nOPERACIONES REALIZADAS \n";
    if (historialOperaciones.empty()) {
        archivo << "(sin operaciones registradas)\n";
    }
    for (auto& r : historialOperaciones) {
        archivo << "[" << r.calculadora << "] "
                << r.num1 << " " << r.operacion << " " << r.num2
                << " = " << r.resultado << "\n";
    }

    archivo << "\nAUTOS REGISTRADOS \n";
    if (historialAutos.empty()) {
        archivo << "(sin autos registrados)\n";
    }
    for (auto& a : historialAutos) {
        archivo << "[" << a.version << "] Marca: " << a.marca
                << " | Precio: $" << a.precio
                << " | Anio: " << a.anio << "\n";
    }

    archivo << "\nPERSONAS REGISTRADAS\n";
    if (historialPersonas.empty()) {
        archivo << "(sin personas registradas)\n";
    }
    for (auto& p : historialPersonas) {
        archivo << "[" << p.version << "] Nombre: " << p.nombre << " " << p.apellidoPaterno << " " << p.apellidoMaterno
                << " | Genero: " << p.genero
                << " | Edad: " << p.edad << "\n";
    }

    archivo.close();
    cout << "datos.txt generado\n";
}

void generarJSON() {
    ofstream archivo("datos.json");
    archivo << "{\n";

    archivo << "  \"operaciones\": [\n";
    for (size_t i = 0; i < historialOperaciones.size(); i++) {
        auto& r = historialOperaciones[i];
        archivo << "    {\"calculadora\": \"" << r.calculadora << "\", "
                << "\"num1\": " << r.num1 << ", "
                << "\"num2\": " << r.num2 << ", "
                << "\"operacion\": \"" << r.operacion << "\", "
                << "\"resultado\": " << r.resultado << "}";
        archivo << (i + 1 < historialOperaciones.size() ? ",\n" : "\n");
    }
    archivo << "  ],\n";

    archivo << "  \"autos\": [\n";
    for (size_t i = 0; i < historialAutos.size(); i++) {
        auto& a = historialAutos[i];
        archivo << "    {\"version\": \"" << a.version << "\", "
                << "\"marca\": \"" << a.marca << "\", "
                << "\"precio\": " << a.precio << ", "
                << "\"anio\": " << a.anio << "}";
        archivo << (i + 1 < historialAutos.size() ? ",\n" : "\n");
    }
    archivo << "  ],\n";

    archivo << "  \"personas\": [\n";
    for (size_t i = 0; i < historialPersonas.size(); i++) {
        auto& p = historialPersonas[i];
        archivo << "    {\"version\": \"" << p.version << "\", "
                << "\"nombre\": \"" << p.nombre << "\", "
                << "\"apellidoPaterno\": \"" << p.apellidoPaterno << "\", "
                << "\"apellidoMaterno\": \"" << p.apellidoMaterno << "\", "
                << "\"genero\": \"" << p.genero << "\", "
                << "\"edad\": " << p.edad << "}";
        archivo << (i + 1 < historialPersonas.size() ? ",\n" : "\n");
    }
    archivo << "  ]\n";

    archivo << "}\n";
    archivo.close();
    cout << "datos.json generado\n";
}

void generarCSV() {
    ofstream archivo("datos.csv");

    archivo << "tipo,calculadora_o_version,dato1,dato2,dato3,dato4,resultado\n";

    for (auto& r : historialOperaciones) {
        archivo << "operacion," << r.calculadora << ","
                << r.num1 << "," << r.operacion << "," << r.num2 << ",,"
                << r.resultado << "\n";
    }

    for (auto& a : historialAutos) {
        archivo << "auto," << a.version << ","
                << a.marca << "," << a.precio << "," << a.anio << ",,\n";
    }

    for (auto& p : historialPersonas) {
        archivo << "persona," << p.version << ","
                << p.nombre << " " << p.apellidoPaterno << " " << p.apellidoMaterno << ","
                << p.genero << "," << p.edad << ",,\n";
    }

    archivo.close();
    cout << "datos.csv generado\n";
}

void generarXML() {
    ofstream archivo("datos.xml");
    archivo << "<sesion>\n";

    archivo << "  <operaciones>\n";
    for (auto& r : historialOperaciones) {
        archivo << "    <operacion calculadora=\"" << r.calculadora << "\">\n";
        archivo << "      <num1>" << r.num1 << "</num1>\n";
        archivo << "      <operador>" << r.operacion << "</operador>\n";
        archivo << "      <num2>" << r.num2 << "</num2>\n";
        archivo << "      <resultado>" << r.resultado << "</resultado>\n";
        archivo << "    </operacion>\n";
    }
    archivo << "  </operaciones>\n";

    archivo << "  <autos>\n";
    for (auto& a : historialAutos) {
        archivo << "    <auto version=\"" << a.version << "\">\n";
        archivo << "      <marca>" << a.marca << "</marca>\n";
        archivo << "      <precio>" << a.precio << "</precio>\n";
        archivo << "      <anio>" << a.anio << "</anio>\n";
        archivo << "    </auto>\n";
    }
    archivo << "  </autos>\n";

    archivo << "  <personas>\n";
    for (auto& p : historialPersonas) {
        archivo << "    <persona version=\"" << p.version << "\">\n";
        archivo << "      <nombre>" << p.nombre << "</nombre>\n";
        archivo << "      <apellidoPaterno>" << p.apellidoPaterno << "</apellidoPaterno>\n";
        archivo << "      <apellidoMaterno>" << p.apellidoMaterno << "</apellidoMaterno>\n";
        archivo << "      <genero>" << p.genero << "</genero>\n";
        archivo << "      <edad>" << p.edad << "</edad>\n";
        archivo << "    </persona>\n";
    }
    archivo << "  </personas>\n";

    archivo << "</sesion>\n";
    archivo.close();
    cout << "datos.xml generado\n";
}
