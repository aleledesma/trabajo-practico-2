#ifndef VERTICAL_H
#define VERTICAL_H

#include "estacion.h"

class Vertical : public Estacion
{
public:
    Vertical(int x, int y);
    void comprobaciones(int arriba, int abajo, int izq, int derecha);
};

#endif // VERTICAL_H
