#ifndef ESTACION_H
#define ESTACION_H


class Estacion
{
private:
    int x;
    int y;
public:
    Estacion(int x, int y);
    virtual void comprobaciones()=0;
    int getX() const;
    void setX(int newX);
    int getY() const;
    void setY(int newY);
};

#endif // ESTACION_H
