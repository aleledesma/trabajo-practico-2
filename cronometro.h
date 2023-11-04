#ifndef CRONOMETRO_H
#define CRONOMETRO_H


class Cronometro
{
private:
    int segundosEstablecidos;
    int contadorSegundos;
public:
    Cronometro(int segundos);
    void decrementar();
    void reiniciar();
    int getContadorSegundos() const;
    int getSegundosEstablecidos() const;
};

#endif // CRONOMETRO_H
