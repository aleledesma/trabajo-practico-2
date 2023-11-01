#ifndef ESTACION_H
#define ESTACION_H
#include "tablero.h"

class Estacion
{
private:
    int x;
    int y;
    int tipo;
    Tablero* tablero;//esto lo necesitamos para preguntarle al tablero si una estacion esta conectada con el metodo comprobaciones
public:
    Estacion(int x, int y);
    Estacion(int x, int y, Tablero* t);
    virtual bool comprobaciones(int filaDeColocacion, int columnaDeColocacion)=0;
    int getX() const;
    void setX(int newX);
    int getY() const;
    void setY(int newY);
    int getTipo();
    void setTipo(int t);
    void setTablero(Tablero* t);
    Tablero* getTablero();
};

#endif // ESTACION_H
