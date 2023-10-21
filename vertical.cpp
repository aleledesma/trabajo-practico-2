#include "vertical.h"

Vertical::Vertical(int x, int y, Tablero* t) :  Estacion(x, y, t)
{
    this->tablero = this->getTablero();
}

bool Vertical::comprobaciones()
{
    if(this->tablero->getEnPos(this->getX()-1,this->getY())==5 || this->tablero->getEnPos(this->getX()+1,this->getY())==5)
    {
        std::cout<<"Estacion "<<this->getTipo()<<" conectada con exito"<<std::endl;
        return true;
    }
    return false;
}
