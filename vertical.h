#ifndef VERTICAL_H
#define VERTICAL_H

#include "estacion.h"

class Vertical : public Estacion
{
private:
    Tablero* tablero;
public:
    Vertical(int x, int y, Tablero* t);
    bool comprobaciones(int filaDeColocacion, int columnaDeColocacion) override;
};

#endif // VERTICAL_H
