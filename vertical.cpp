#include "vertical.h"

Vertical::Vertical(int x, int y, Tablero* t) :  Estacion(x, y, t)
{
    this->tablero = this->getTablero();
}

bool Vertical::comprobaciones(int filaDeColocacion, int columnaDeColocacion)
{
    return ((tablero->getEnPos(this->getX() - 1, this->getY()) == 0) || (tablero->getEnPos(this->getX() + 1, this->getY()) == 0)) && (columnaDeColocacion == this->getY());
}
