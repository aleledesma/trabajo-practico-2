#ifndef HORIZONTAL_H
#define HORIZONTAL_H

#include "estacion.h"

class Horizontal : public Estacion
{
private:
    Tablero* tablero;
public:
    Horizontal(int x, int y, Tablero* t);
    bool comprobaciones() override;
};

#endif // HORIZONTAL_H
