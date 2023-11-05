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
        
        if(valor==3 && columna==0)
        {
            columna++;
        }
        if(valor==3 && columna==this->columnas-1)
        {
            columna--;
        }
        if(valor==4 && fila==0)
        {
            fila++;
        }
        if(valor==4 && fila==this->filas-1)
        {
            fila--;
        }
        this->matriz[fila][columna] = valor;
        return true;
    }
    return false;
}

int Tablero::getEnPos(int fila, int columna)
{
    if(fila < this->filas && columna < this->columnas) {
        return this->matriz[fila][columna];
    }
    return -1; //en el caso de que la posición este fuera de las dimenciones de la matriz

}

Tablero::~Tablero()
{
    // Liberar matriz
    for(int i = 0; i<this->filas; i++) {
        delete[] this->matriz[i];
    }
    delete[] this->matriz;
    //liberar vector estaciones
    //this->estaciones.clear(); //elimina todos los elementos.
}
