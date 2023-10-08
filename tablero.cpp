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
    return this->matriz[fila][columna];
}

void Tablero::ponerEstacion(int fila, int columuna)
{
    if(fila < this->filas && columuna < this->columnas) {
        Estacion* nuevaEstacion = new Comun(fila, columuna);
        int tipoEstacion = rand() % 4+1;
        std::cout<<"Tipo de est: "<<tipoEstacion<<std::endl;
        this->matriz[fila][columuna] = tipoEstacion;
        switch(tipoEstacion) {
        case 1: nuevaEstacion = new Comun(fila, columuna); nuevaEstacion->setTipo(1); break;//esto genera una fuga de memoria, destruir estaciones cuando sea necesario
        case 2: nuevaEstacion = new Multiple(fila, columuna); nuevaEstacion->setTipo(2); break;
        case 3: nuevaEstacion = new Horizontal(fila, columuna); nuevaEstacion->setTipo(3); break;
        case 4: nuevaEstacion = new Vertical(fila, columuna); nuevaEstacion->setTipo(4); break;
        default: break;
        }
        this->estaciones.push_back(nuevaEstacion);
    }

}

void Tablero::ponerRuta()
{

}

int Tablero::getEstacionDeVector(int indice)
{
    return this->estaciones[indice]->getTipo();
}

Tablero::~Tablero()
{
    for(int i = 0; i<this->filas; i++) {
        delete[] this->matriz[i];
    }
    delete[] this->matriz;
}
