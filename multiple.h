#ifndef MULTIPLE_H
#define MULTIPLE_H

#include "estacion.h"

class Multiple : public Estacion
{
public:
    Multiple(int x, int y);
    void comprobaciones(int arriba, int abajo, int izq, int derecha) override;

};

#endif // MULTIPLE_H
