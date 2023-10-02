#include "juego.h"

Juego::Juego(int filas, int columnas)
{
    this->tablero = new Tablero(filas, columnas);
    this->filas = filas;
    this->columnas = columnas;
}

int Juego::getFilas() const
{
    return this->filas;
}

int Juego::getColumnas() const
{
    return this->columnas;
}

Juego::~Juego()
{
    delete this->tablero;
}
