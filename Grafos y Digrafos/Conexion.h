#ifndef CONEXION_H
#define CONEXION_H

#include <iostream>
#include <string>

using namespace std;

struct Conexion {
    int nodoInicial;
    int nodoFinal;
    string aristaConexion;
    int tiempo;
    int costo;
};

#endif