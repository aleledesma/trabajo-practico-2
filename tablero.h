#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <cstdlib>
#include <iostream>

class Tablero
{
private:
    int** matriz = nullptr;
    int filas;
    int columnas;
public:
    Tablero(int filas = 10, int columnas = 10);
    bool setEnPos(int fila, int columna, int valor);
    int getEnPos(int fila, int columna);
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
