#ifndef HORIZONTAL_H
#define HORIZONTAL_H

#include "estacion.h"

class Horizontal : public Estacion
{
public:
    Horizontal(int x, int y);
    void comprobaciones() override;
};

#endif // HORIZONTAL_H
