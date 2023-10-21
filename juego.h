#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include <cstdlib>
#include <iostream>

#include "estacion.h"
#include "comun.h"
#include "vertical.h"
#include "horizontal.h"
#include "multiple.h"


class Juego
{
private:
    Tablero* tablero = nullptr;
    int filas;
    int columnas;
    std::vector<Estacion*> estaciones;
public:
    Juego(int filas = 10, int columnas = 10);
    int getFilas() const;
    int getColumnas() const;
    int** iniciarJuego(int segundos);
    int genNumero(int max);
    Tablero* getReferenciaTablero();//esto lo necesitamos para acceder al vector de estaciones cuando apretamos el boton "jugar xd"

    void ponerEstacion(int fila, int columuna);
    bool ponerRuta(int fila, int columna);
    bool comprobarRuta(int fila, int columna);
    bool comprobarConexionEstaciones();
    int getTipoEstacion(int indice);
    bool comprobarExistencia(int fila, int columna, char* entidad);

    ~Juego();
};

#endif // JUEGO_H
