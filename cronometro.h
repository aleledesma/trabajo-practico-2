#ifndef CRONOMETRO_H
#define CRONOMETRO_H


class Cronometro
{
private:
    int segundosEstablecidos;
    int contadorSegundos;
public:
    Cronometro(int segundos);
    Cronometro();
    void decrementar();
    void reiniciar();
    int getContadorSegundos() const;
    int getSegundosEstablecidos() const;
    void setSegundosEstablecidos(int s);
    void setContadorSegundos(int s);
};

#endif // CRONOMETRO_H
