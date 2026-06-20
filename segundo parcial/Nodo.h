#ifndef NODO_H
#define NODO_H

#include "Auto.h"

class Nodo {
public:
    Auto dato;
    Nodo* siguiente;

    Nodo() {
        siguiente = NULL;
    }
};

#endif