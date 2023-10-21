#ifndef MULTIPLE_H
#define MULTIPLE_H

#include "estacion.h"

class Multiple : public Estacion
{
public:
    Multiple(int x, int y, Tablero* t);
    bool comprobaciones() override;

};

#endif // MULTIPLE_H
