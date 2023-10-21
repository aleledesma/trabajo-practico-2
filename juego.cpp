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
        //nota: el metodo ponerEstacion es quien deberia generar las posiciones fila y columna en donde colocar la estación, ya que desde ahi podemos contemplar los distintos casos (por ejemplo que las estaciones verticales no esten pegadas a los bordes, etc)
        int fila = this->genNumero(this->filas);
        int columna = this->genNumero(this->columnas);
        posiciones[i][0] = fila;
        posiciones[i][1] = columna;
        this->ponerEstacion(fila,columna);
    }
    return posiciones;
}

int Juego::genNumero(int max)
{
    int num = rand() % max; //+1?
    return num;
}

void Juego::ponerEstacion(int fila, int columuna)
{
    if(fila < this->filas && columuna < this->columnas) {
        Estacion* nuevaEstacion;
        int tipoEstacion = rand() % 4+1;
      //  std::cout<<"Tipo de est: "<<tipoEstacion<<std::endl;
        this->tablero->setEnPos(fila,columuna,tipoEstacion);
       // std::cout<<"Est: "<<this->matriz[fila][columuna]<<std::endl;
        switch(tipoEstacion) {
        case 1: nuevaEstacion = new Comun(fila, columuna, this->tablero); nuevaEstacion->setTipo(1); break;
        case 2: nuevaEstacion = new Multiple(fila, columuna, this->tablero); nuevaEstacion->setTipo(2); break;
        case 3: nuevaEstacion = new Horizontal(fila, columuna, this->tablero); nuevaEstacion->setTipo(3); break;
        case 4: nuevaEstacion = new Vertical(fila, columuna, this->tablero); nuevaEstacion->setTipo(4); break;
        default: break;
        }
        this->estaciones.push_back(nuevaEstacion);
    }

}

bool Juego::ponerRuta(int fila, int columna)
{
    if(comprobarRuta(fila, columna)) {
        this->tablero->setEnPos(fila,columna,5);
        return true;
    }
    return false;
}

bool Juego::comprobarRuta(int fila, int columna)
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

bool Juego::comprobarConexionEstaciones()
{
    for(unsigned long i=0; i<this->estaciones.size(); i++)//tiene que ser unsigned long porque qt es una masa
    {
        if(this->estaciones[i]->comprobaciones()==false)
        {
            //std::cout<<"Estacion de tipo "<<this->estaciones[i]->getTipo()<<" no esta conectada"<<std::endl;
            return false;//si alguna de las estaciones no esta conectada, devolvemos falso
        }
    }
    return true;//si todas las estaciones estan conectadas, tenemos que crear una estacion nueva
}

int Juego::getTipoEstacion(int indice)
{
    return this->estaciones[indice]->getTipo();
}

bool Juego::comprobarExistencia(int fila, int columna, char *entidad)
{
    int valorEnMatriz = this->tablero->getEnPos(fila,columna);

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

Tablero *Juego::getReferenciaTablero()
{
    return this->tablero;
}

Juego::~Juego()
{
    this->estaciones.clear();
    delete this->tablero;
}
