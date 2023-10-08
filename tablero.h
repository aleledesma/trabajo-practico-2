#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <cstdlib>
#include <iostream>

#include "estacion.h"
#include "comun.h"
#include "vertical.h"
#include "horizontal.h"
#include "multiple.h"

class Tablero
{
private:
    int** matriz = nullptr;
    std::vector<Estacion*> estaciones;
    int filas;
    int columnas;
public:
    Tablero(int filas = 10, int columnas = 10);
    bool setEnPos(int fila, int columna, int valor);
    int getEnPos(int fila, int columna);
    void ponerEstacion(int fila, int columuna);
    void ponerRuta();
    int getEstacionDeVector(int indice);
    ~Tablero();
};

#endif // TABLERO_H
/* Valores del tablero:
 * 0: celda vacía.
 * 1: estación común.
 * 2: estación múltiple.
 * 3: estación horizontal.
 * 4: estación vertical
 * 5: ruta vertical
 * 6: ruta horizontal
 */
