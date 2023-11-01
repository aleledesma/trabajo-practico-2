#include "comun.h"

Comun::Comun(int x, int y, Tablero* t) : Estacion(x, y, t)
{
    this->tablero = t;
}

bool Comun::comprobaciones(int filaDeColocacion, int columnaDeColocacion)
{
    //si se usa como vertical:
    if(filaDeColocacion != this->getX()) {
        return (tablero->getEnPos(this->getX(), this->getY() - 1) == 0) && (tablero->getEnPos(this->getX(), this->getY() + 1) == 0);
    }
    //si se usa como horizontal:
    else if(columnaDeColocacion != this->getY()) {
        return (tablero->getEnPos(this->getX() - 1, this->getY()) == 0) && (tablero->getEnPos(this->getX() + 1, this->getY()) == 0);
    }

    //falta abarcar el caso en que la estacion este colocada a un borde.

}

