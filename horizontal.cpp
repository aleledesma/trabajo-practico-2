#include "horizontal.h"

Horizontal::Horizontal(int x, int y, Tablero* t) : Estacion(x, y, t)
{
    this->tablero = t;
}

bool Horizontal::comprobaciones()
{
    if(this->tablero->getEnPos(this->getX(),this->getY()-1)==6 || this->tablero->getEnPos(this->getX(),this->getY()+1)==6)
    {
        std::cout<<"Estacion "<<this->getTipo()<<" conectada con exito"<<std::endl;
        return true;
    }
    return false;
}
