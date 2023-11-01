#ifndef HORIZONTAL_H
#define HORIZONTAL_H

#include "estacion.h"

class Horizontal : public Estacion
{
private:
    Tablero* tablero;
public:
    Horizontal(int x, int y, Tablero* t);
    bool comprobaciones(int filaDeColocacion, int columnaDeColocacion) override;
};

#endif // HORIZONTAL_H
