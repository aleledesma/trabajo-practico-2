#ifndef MULTIPLE_H
#define MULTIPLE_H

#include "estacion.h"

class Multiple : public Estacion
{
private:
    Tablero* tablero;
public:
    Multiple(int x, int y, Tablero* t);
    bool comprobaciones(int filaDeColocacion, int columnaDeColocacion) override;

};

#endif // MULTIPLE_H
