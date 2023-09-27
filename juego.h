#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"


class Juego
{
private:
    Tablero* tablero = nullptr;
public:
    Juego(int filas = 10, int columnas = 10);
};

#endif // JUEGO_H
