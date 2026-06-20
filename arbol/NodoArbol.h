#ifndef NODOARBOL_H
#define NODOARBOL_H

#include "Auto.h"

class NodoArbol {
public:
    Auto dato;
    NodoArbol* izquierda;
    NodoArbol* derecha;

    NodoArbol() {
        izquierda = NULL;
        derecha = NULL;
    }
};

#endif