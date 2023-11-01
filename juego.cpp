#include "juego.h"

void Juego::setRonda(int newRonda)
{
    ronda = newRonda;
}

int Juego::getRonda() const
{
    return ronda;
}

Juego::Juego(int filas, int columnas)
{
    this->tablero = new Tablero(filas, columnas);
    this->filas = filas;
    this->columnas = columnas;
}

int Juego::getFilas() const
{
    return this->filas;
}

int Juego::getColumnas() const
{
    return this->columnas;
}

int** Juego::iniciarJuego(int segundos)
{
    //iniciar cronometro
    int** posiciones = new int*[2];
    for(int i = 0; i<2; i++) {
        posiciones[i] = new int[2];
        //nota: el metodo ponerEstacion es quien deberia generar las posiciones fila y columna en donde colocar la estación, ya que desde ahi podemos contemplar los distintos casos (por ejemplo que las estaciones verticales no esten pegadas a los bordes, etc)
        int fila = this->genNumero(this->filas);
        int columna = this->genNumero(this->columnas);
        posiciones[i][0] = fila;
        posiciones[i][1] = columna;
        this->ponerEstacion(fila,columna);
    }
    this->ronda++;
    return posiciones;
}

int Juego::genNumero(int max)
{
    int num = rand() % max; //+1?
    return num;
}

void Juego::ponerEstacion(int fila, int columuna)
{
    if(fila < this->filas && columuna < this->columnas) {
        Estacion* nuevaEstacion;
        int tipoEstacion = rand() % 4+1;
      //  std::cout<<"Tipo de est: "<<tipoEstacion<<std::endl;
        this->tablero->setEnPos(fila,columuna,tipoEstacion);
       // std::cout<<"Est: "<<this->matriz[fila][columuna]<<std::endl;
        switch(tipoEstacion) {
        case 1: nuevaEstacion = new Comun(fila, columuna, this->tablero); nuevaEstacion->setTipo(1); break;
        case 2: nuevaEstacion = new Multiple(fila, columuna, this->tablero); nuevaEstacion->setTipo(2); break;
        case 3: nuevaEstacion = new Horizontal(fila, columuna, this->tablero); nuevaEstacion->setTipo(3); break;
        case 4: nuevaEstacion = new Vertical(fila, columuna, this->tablero); nuevaEstacion->setTipo(4); break;
        default: break;
        }
        this->estaciones.push_back(nuevaEstacion);
    }

}

Estacion* Juego::estacionCerca(int fila, int columna) {
    Estacion* est;
    est = buscarEstacion(fila - 1, columna); //checkea arriba
    if(est != nullptr) return est; //si hay la devuelve
    est = buscarEstacion(fila + 1, columna); //checkea abajo
    if(est != nullptr) return est; //si hay la devuelve
    est = buscarEstacion(fila, columna - 1); //checkea izquierda
    if(est != nullptr) return est; //si hay la devuelve
    est = buscarEstacion(fila, columna + 1); //checkea derecha
    if(est != nullptr) return est; //si hay la devuelve
    return nullptr; //si no encuentra ninguna estacion devuelve nullptr
}

bool Juego::sePuedeConectarRuta(int fila, int columna) {
    bool res = false;
    if(this->rutasDeRonda.size() == 0) return true; //si la ruta a colocar es la primera
    if(fila == this->ultimaRuta.first) { //si la ruta nueva va en sentido horizontal
        res = (this->ultimaRuta.second == columna - 1) || (this->ultimaRuta.second == columna + 1);
    }
    else if(columna == this->ultimaRuta.second) { //si la ruta nueva va en sentido vertical
        res = (this->ultimaRuta.first == fila - 1) || (this->ultimaRuta.first == fila + 1);
    }
    return res;
}

bool Juego::ponerRuta(int fila, int columna)
{
    if(comprobarRuta(fila, columna) && sePuedeConectarRuta(fila, columna)) {
        this->tablero->setEnPos(fila,columna,5); //cambiar para que se calcule si la ruta debe ser v o h
        pair<int,int> coordsRuta(fila, columna);
        this->rutasDeRonda.push_back(coordsRuta);
        this->ultimaRuta = coordsRuta;

        Estacion* est = estacionCerca(fila, columna);
        if(est != nullptr) {
            if(this->rutasDeRonda.size() > 1) {
                if(est->comprobaciones(fila, columna)) {
                    cout<<"Estacion conectada"<<endl;
                }
            }
        }
        return true;
    }
    return false;
}

bool Juego::comprobarRuta(int fila, int columna)
{
    bool res = false;
//  Es innecesario validar que fila y columna este dentro de las dimenciones.
    bool izq = (columna > 0) ? (this->comprobarDisponiblidadDeConexion(fila, columna - 1, "estacion", fila, columna) || this->comprobarDisponiblidadDeConexion(fila, columna - 1, "ruta")) : false;
    bool der = (columna < (this->columnas - 1)) ? (this->comprobarDisponiblidadDeConexion(fila, columna + 1, "estacion", fila, columna) || this->comprobarDisponiblidadDeConexion(fila, columna + 1, "ruta")) : false;
    bool arr = (fila > 0) ? (this->comprobarDisponiblidadDeConexion(fila - 1, columna, "estacion", fila, columna) || this->comprobarDisponiblidadDeConexion(fila - 1, columna, "ruta")) : false;
    bool abj = (fila < (this->filas - 1)) ? (this->comprobarDisponiblidadDeConexion(fila + 1, columna, "estacion", fila, columna) || this->comprobarDisponiblidadDeConexion(fila + 1, columna, "ruta")) : false;
    res = (this->comprobarExistencia(fila, columna, "vacio")) && (izq || der || arr || abj);

    return res;
}

int Juego::getTipoEstacion(int indice)
{
    return this->estaciones[indice]->getTipo();
}

bool Juego::comprobarExistencia(int fila, int columna, char *entidad)
{
    int valorEnMatriz = this->tablero->getEnPos(fila,columna);

    bool respuesta = false;
    if(entidad == "estacion") {
        respuesta = valorEnMatriz > 0 && valorEnMatriz <5;
        }
    else if(entidad == "ruta") {
        respuesta = valorEnMatriz == 5 || valorEnMatriz == 6;
        }
    else if(entidad == "vacio") {
        respuesta = valorEnMatriz == 0;
    }
    return respuesta;
}

bool Juego::comprobarDisponiblidadDeConexion(int fila, int columna, char *entidad, int filaOriginal, int columnaOriginal) //esto de fila/col original esta feo ponerlo como param aca, habria que dividir esto en 2 metodos y que solo el que compruebe las estaciones lo reciba
{
    bool respuesta = false;
    if(entidad == "estacion") {
        respuesta = this->comprobarExistencia(fila, columna, entidad);
        if(respuesta) {
            Estacion* estacionBuscada = this->buscarEstacion(fila, columna);
            if(estacionBuscada != nullptr) {
                respuesta = estacionBuscada->comprobaciones(filaOriginal, columnaOriginal);
            } else {
                respuesta = false;
            }
        }
    }
    else if(entidad == "ruta") {
        respuesta = this->comprobarExistencia(fila, columna, entidad);
        if(respuesta) {
            auto it = find_if(this->rutasDeRonda.begin(), this->rutasDeRonda.end(), [fila, columna](pair<int,int> par){
                return par.first == fila && par.second == columna;
            });
            if(it == this->rutasDeRonda.end()) {
                respuesta = false;
            }
        }
    }
    return respuesta;
}

Estacion *Juego::buscarEstacion(int x, int y)
{
    Estacion* estBuscada = nullptr;
    auto res = find_if(this->estaciones.begin(), this->estaciones.end(), [x,y](Estacion* estacion){
        return estacion->getX() == x && estacion->getY() == y;
    });
    if(res != this->estaciones.end()) {
        estBuscada = *res;
    }
    return estBuscada;
}

Tablero *Juego::getReferenciaTablero()
{
    return this->tablero;
}

Juego::~Juego()
{
    this->estaciones.clear();
    delete this->tablero;
}
