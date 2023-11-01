#include "multiple.h"

Multiple::Multiple(int x, int y, Tablero* t) :  Estacion(x, y, t)
{
    this->tablero = t;
}

bool Multiple::comprobaciones(int filaDeColocacion, int columnaDeColocacion)
{
    return true;
}
