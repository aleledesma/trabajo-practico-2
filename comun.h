#ifndef COMUN_H
#define COMUN_H

#include "estacion.h"

class Comun : public Estacion
{
public:
    Comun(int x, int y);
    void comprobaciones(int arriba, int abajo, int izq, int derecha);
};

#endif // COMUN_H
