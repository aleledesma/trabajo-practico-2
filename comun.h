#ifndef COMUN_H
#define COMUN_H

#include "estacion.h"

class Comun : public Estacion
{
public:
    Comun(int x, int y, Tablero* t);
    bool comprobaciones() override;
};

#endif // COMUN_H
