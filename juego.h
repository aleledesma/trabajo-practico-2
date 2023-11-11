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

#include <vector>
#include <map>
#include <algorithm>

#include "qfile.h"

#include "cronometro.h"

#include <QMessageBox>

using namespace std;

struct estacion{
    int tipo;
    int posX;
    int posY;
};

struct ruta{
    pair<int, int> ultimaRuta;
};

struct cantidades{
    int tableroX;
    int tableroY;
    int cantidadEstaciones;
    int cantidadRutas;
};

struct tiempo{
    int segundosRestantes;
    int segundosTotales;
};

class Juego
{
private:
    Tablero* tablero = nullptr;
    int filas;
    int columnas;
    int ronda = 0;
    vector<pair<int,int>> rutasDeRonda;
    vector<pair<int,int>> rutasTotales;
    pair<int, int> ultimaRuta;
    std::vector<Estacion*> estaciones;
    bool overrideComprobacion;
    Cronometro* cronometro;
    tiempo t;
public:
    Juego(int filas = 10, int columnas = 10);
    void setFilas(int f);
    void setColumnas(int c);
    int getFilas() const;
    int getColumnas() const;
    int** iniciarJuego();
    int genNumero(int max);
    Tablero* getReferenciaTablero();
    int* ponerEstacion();
    bool ponerRuta(int fila, int columna);
    bool comprobarRuta(int fila, int columna);
    int getTipoEstacion(int indice);
    bool comprobarExistencia(int fila, int columna, char* entidad);
    bool comprobarDisponiblidadDeConexion(int fila, int columna, char* entidad, int filaOriginal = 0, int columnaOriginal = 0);
    Estacion* buscarEstacion(int x, int y);
    Estacion* estacionCerca(int fila, int columna);
    Estacion* estacionCercaDiagonal(int fila, int columna);
    bool sePuedeConectarRuta(int fila, int columna);
    bool comprobarConexion(int fila, int columna);
    int* nuevaRonda();

    bool validezEstacion(int fila, int columna, int tipo);
    void victoria();
    void setCronometro(Cronometro* c);
    int getSegundosRestantes();
    int getSegundosTotales();
    Cronometro* getReferenciaCronometro();
    void instanciarTablero();
    pair<int, int> getCoordenadasRutaIndice(int indice);
    int getCantidadRutas();
    int getCantidadEstaciones();
    Estacion* getReferenciaEstacionIndice(int indice);
    void guardarPartida();
    bool cargarPartida();

    ~Juego();
    void setRonda(int newRonda);
    int getRonda() const;
};

#endif // JUEGO_H
