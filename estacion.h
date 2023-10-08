#ifndef ESTACION_H
#define ESTACION_H


class Estacion
{
private:
    int x;
    int y;
    int tipo;
public:
    Estacion(int x, int y);
    virtual void comprobaciones()=0;//este metodo no puede tener parametros
    int getX() const;
    void setX(int newX);
    int getY() const;
    void setY(int newY);
    int getTipo();
    void setTipo(int t);
};

#endif // ESTACION_H
