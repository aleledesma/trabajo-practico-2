#include "comun.h"

Comun::Comun(int x, int y, Tablero* t) : Estacion(x, y, t)
{
    this->tablero = t;
}

bool Comun::comprobaciones(int filaDeColocacion, int columnaDeColocacion)
{
    //si se usa como vertical:
    if(filaDeColocacion != this->getX()) {
        int izq = this->tablero->getEnPos(this->getX(), this->getY() - 1);
        int der = this->tablero->getEnPos(this->getX(), this->getY() + 1);
        return ((izq == 0 || izq == -1) && (der == 0 || der == -1));
    }
    //si se usa como horizontal:
    else if(columnaDeColocacion != this->getY()) {
        int arr = tablero->getEnPos(this->getX() - 1, this->getY());
        int abj = tablero->getEnPos(this->getX() + 1, this->getY());
        return ((arr == 0 || arr == -1) && (abj == 0 || abj == -1));
    }
}

