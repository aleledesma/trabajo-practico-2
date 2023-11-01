#ifndef COMUN_H
#define COMUN_H

#include "estacion.h"

class Comun : public Estacion
{
private:
    Tablero* tablero;
public:
    Comun(int x, int y, Tablero* t);
    bool comprobaciones(int filaDeColocacion, int columnaDeColocacion) override;
};

#endif // COMUN_H
