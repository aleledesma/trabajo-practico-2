#include "tablero.h"

Tablero::Tablero(int filas, int columnas)
{
    this->filas = filas;
    this->columnas = columnas;
    this->matriz = new int*[filas];
    for(int i = 0; i<filas; i++) {
        this->matriz[i] = new int[columnas];
        for(int j = 0; j<columnas; j++) {
            this->matriz[i][j] = 0; // inicialización de todas las celdas en 0 -> todas las celdas vacias
        }
    }
}

bool Tablero::setEnPos(int fila, int columna, int valor)
{
    if((fila < this->filas) && (columna < this->columnas) && (this->matriz[fila][columna] == 0)) {
        this->matriz[fila][columna] = valor;
        return true;
    } else {
        return false;
    }
}

int Tablero::getEnPos(int fila, int columna)
{

}
