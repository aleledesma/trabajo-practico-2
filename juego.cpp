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

int** Juego::iniciarJuego(int segundos)
{
    //iniciar cronometro
    int** posiciones = new int*[2];
    for(int i = 0; i<2; i++) {
        posiciones[i] = new int[2];
        int fila = this->genNumero(this->filas);
        int columna = this->genNumero(this->columnas);
        posiciones[i][0] = fila;
        posiciones[i][1] = columna;
        this->tablero->ponerEstacion(fila, columna);
    }
    return posiciones;
}

int Juego::genNumero(int max)
{
    int num = rand() % max; //+1?
    return num;
}

Tablero *Juego::getReferenciaTablero()
{
    return this->tablero;
}

Juego::~Juego()
{
    delete this->tablero;
}
