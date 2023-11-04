#include "cronometro.h"

int Cronometro::getContadorSegundos() const
{
    return contadorSegundos;
}

int Cronometro::getSegundosEstablecidos() const
{
    return segundosEstablecidos;
}

Cronometro::Cronometro(int segundos)
{
    this->segundosEstablecidos = segundos;
    this->contadorSegundos = segundos;
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
