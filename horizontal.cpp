#include "horizontal.h"

Horizontal::Horizontal(int x, int y, Tablero* t) : Estacion(x, y, t)
{
    this->tablero = t;
}

bool Horizontal::comprobaciones()
{
    //if(this->tablero->getEnPos(this->getY(),this->getX())==5)//esto tiene que ser 6, no 5
    return true;
}
