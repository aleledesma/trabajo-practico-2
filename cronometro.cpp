#include "cronometro.h"

int Cronometro::getContadorSegundos() const
{
    return contadorSegundos;
}

int Cronometro::getSegundosEstablecidos() const
{
    return segundosEstablecidos;
}

void Cronometro::setSegundosEstablecidos(int s)
{
    this->segundosEstablecidos = s;
}

void Cronometro::setContadorSegundos(int s)
{
    this->contadorSegundos=s;
}

Cronometro::Cronometro(int segundos)
{
    this->segundosEstablecidos = segundos;
    this->contadorSegundos = segundos;
}

Cronometro::Cronometro()
{

}

void Cronometro::decrementar()
{
    if(this->contadorSegundos > 0) {
        this->contadorSegundos--;
    }
}

void Cronometro::reiniciar()
{
    this->contadorSegundos = this->segundosEstablecidos;
}
