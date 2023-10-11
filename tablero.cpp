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

void Tablero::ponerEstacion(int fila, int columuna)
{
    if(fila < this->filas && columuna < this->columnas) {
        Estacion* nuevaEstacion;
        int tipoEstacion = rand() % 4+1;
      //  std::cout<<"Tipo de est: "<<tipoEstacion<<std::endl;
        this->matriz[fila][columuna] = tipoEstacion;
       // std::cout<<"Est: "<<this->matriz[fila][columuna]<<std::endl;
        switch(tipoEstacion) {
        case 1: nuevaEstacion = new Comun(fila, columuna); nuevaEstacion->setTipo(1); break;
        case 2: nuevaEstacion = new Multiple(fila, columuna); nuevaEstacion->setTipo(2); break;
        case 3: nuevaEstacion = new Horizontal(fila, columuna); nuevaEstacion->setTipo(3); break;
        case 4: nuevaEstacion = new Vertical(fila, columuna); nuevaEstacion->setTipo(4); break;
        default: break;
        }
        this->estaciones.push_back(nuevaEstacion);
    }

}

bool Tablero::ponerRuta(int fila, int columna)
{
    if(comprobarRuta(fila, columna)) {
        this->matriz[fila][columna] = 5;
        return true;
    }
    return false;
}

bool Tablero::comprobarRuta(int fila, int columna)
{
    bool res = false;
//  Es innecesario validar que fila y columna este dentro de las dimenciones.
    bool izq = (columna > 0) ? (this->comprobarExistencia(fila, columna - 1, "estacion") || this->comprobarExistencia(fila, columna - 1, "ruta")) : false;
    bool der = (columna < (this->columnas - 1)) ? (this->comprobarExistencia(fila, columna + 1, "estacion") || this->comprobarExistencia(fila, columna + 1, "ruta")) : false;
    bool arr = (fila > 0) ? (this->comprobarExistencia(fila - 1, columna, "estacion") || this->comprobarExistencia(fila - 1, columna, "ruta")) : false;
    bool abj = (fila < (this->filas - 1)) ? (this->comprobarExistencia(fila + 1, columna, "estacion") || this->comprobarExistencia(fila + 1, columna, "ruta")) : false;
    res = (this->comprobarExistencia(fila, columna, "vacio")) && (izq || der || arr || abj);

    return res;
}

int Tablero::getEstacionDeVector(int indice)
{
    return this->estaciones[indice]->getTipo();
}

bool Tablero::comprobarExistencia(int fila, int columna, char *entidad)
{
    int valorEnMatriz = this->matriz[fila][columna];
    bool respuesta = false;
    if(entidad == "estacion") {
        respuesta = valorEnMatriz > 0 && valorEnMatriz <5;
    }
    else if(entidad == "ruta") {
        respuesta = valorEnMatriz == 5 || valorEnMatriz == 6;
    }
    else if(entidad == "vacio") {
        respuesta = valorEnMatriz == 0;
    }
    return respuesta;
}

Tablero::~Tablero()
{
    // Liberar matriz
    for(int i = 0; i<this->filas; i++) {
        delete[] this->matriz[i];
    }
    delete[] this->matriz;
    //liberar vector estaciones
    this->estaciones.clear(); //elimina todos los elementos.
}
