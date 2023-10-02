#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"


class Juego
{
private:
    Tablero* tablero = nullptr;
    int filas;
    int columnas;
public:
    Juego(int filas = 10, int columnas = 10);
    int getFilas() const;
    int getColumnas() const;
    ~Juego();
};

#endif // JUEGO_H
