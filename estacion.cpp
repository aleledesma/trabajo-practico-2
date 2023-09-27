#include "estacion.h"

Estacion::Estacion(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Estacion::getX() const
{
    return x;
}

void Estacion::setX(int newX)
{
    x = newX;
}

int Estacion::getY() const
{
    return y;
}

void Estacion::setY(int newY)
{
    y = newY;
}
