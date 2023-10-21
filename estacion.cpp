#include "estacion.h"

Estacion::Estacion(int x, int y)
{
    this->x = x;
    this->y = y;
}

Estacion::Estacion(int x, int y, Tablero *t)
{
    this->x = x;
    this->y = y;
    this->tablero = t;
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

int Estacion::getTipo()
{
    return this->tipo;
}

void Estacion::setTipo(int t)
{
    this->tipo = t;
}

void Estacion::setTablero(Tablero *t)
{
    this->tablero = t;
}

Tablero *Estacion::getTablero()
{
    return this->tablero;
}
