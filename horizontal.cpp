#include "horizontal.h"

Horizontal::Horizontal(int x, int y, Tablero* t) : Estacion(x, y, t)
{
    this->tablero = t;
}

bool Horizontal::comprobaciones(int filaDeColocacion, int columnaDeColocacion)
{
    return ((tablero->getEnPos(this->getX(), this->getY() - 1) == 0) || (tablero->getEnPos(this->getX(), this->getY() + 1) == 0)) && (filaDeColocacion == this->getX());
}
