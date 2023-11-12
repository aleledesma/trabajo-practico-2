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

void Juego::setFilas(int f)
{
    this->filas = f;
}

void Juego::setColumnas(int c)
{
    this->columnas = c;
}

void Juego::instanciarTablero()
{
    this->tablero = new Tablero(filas, columnas);
}

int Juego::getFilas() const
{
    return this->filas;
}

int Juego::getColumnas() const
{
    return this->columnas;
}

int** Juego::iniciarJuego()
{
    int** posiciones = new int*[2];
    for(int i = 0; i<2; i++) {
        //nota: el metodo ponerEstacion es quien deberia generar las posiciones fila y columna en donde colocar la estación, ya que desde ahi podemos contemplar los distintos casos (por ejemplo que las estaciones verticales no esten pegadas a los bordes, etc)
        posiciones[i] = this->ponerEstacion();
    }
    this->ronda++;
    return posiciones;
}

int Juego::genNumero(int max)
{
    int num = rand() % max;
    return num;
}

int* Juego::ponerEstacion()
{
    int* posValida = nullptr;
    bool colocada=false;
    int tipoEstacion;
    int fila;
    int columna;
    for(int i=0; i<1000; i++)//si despues de 1000 iteraciones no encuentra una posicion valida, tomarlo como victoria
    {
        tipoEstacion = rand() % 4+1;
        fila = rand() % (this->filas);
        columna = rand() % (this->columnas);
        if((validezEstacion(fila,columna,tipoEstacion)) && (estacionCerca(fila, columna) == nullptr) && (estacionCercaDiagonal(fila, columna) == nullptr) && (!rutaCerca(fila, columna)))
        {
            colocada = true;
            i=1001;
            break;
        }
        else
        {
            colocada=false;
        }
    }
    if(!colocada)
    {
        victoria();
    }

    if(fila < this->filas && columna < this->columnas && colocada) {
        posValida = new int[2];
        posValida[0] = fila;
        posValida[1] = columna;
        Estacion* nuevaEstacion;
        this->tablero->setEnPos(fila,columna,tipoEstacion);
        switch(tipoEstacion) {
        case 1: nuevaEstacion = new Comun(fila, columna, this->tablero); nuevaEstacion->setTipo(1); break;
        case 2: nuevaEstacion = new Multiple(fila, columna, this->tablero); nuevaEstacion->setTipo(2); break;
        case 3: nuevaEstacion = new Horizontal(fila, columna, this->tablero); nuevaEstacion->setTipo(3); break;
        case 4: nuevaEstacion = new Vertical(fila, columna, this->tablero); nuevaEstacion->setTipo(4); break;
        default: break;
        }
        this->estaciones.push_back(nuevaEstacion);
    }
    return posValida;
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

int Juego::cantidadEstacionesCerca(int fila, int columna) {
    int cantEstaciones = 0;
    Estacion* est;
    est = buscarEstacion(fila - 1, columna);
    if(est != nullptr) cantEstaciones++;
    est = buscarEstacion(fila + 1, columna);
    if(est != nullptr) cantEstaciones++;
    est = buscarEstacion(fila, columna - 1);
    if(est != nullptr) cantEstaciones++;
    est = buscarEstacion(fila, columna + 1);
    if(est != nullptr) cantEstaciones++;
    return cantEstaciones;
}

bool Juego::rutaCerca(int fila, int columna) {
    bool izq = this->tablero->getEnPos(fila, columna - 1) == 5;
    bool der = this->tablero->getEnPos(fila, columna + 1) == 5;
    bool arr = this->tablero->getEnPos(fila - 1, columna) == 5;
    bool abj = this->tablero->getEnPos(fila + 1, columna) == 5;
    return (izq || der || arr || abj);
}

Estacion* Juego::estacionCercaDiagonal(int fila, int columna) {
    Estacion* est;
    est = buscarEstacion(fila - 1, columna - 1); //esquina superior izquierda
    if(est != nullptr) return est;
    est = buscarEstacion(fila - 1, columna + 1); //esquina superior derecha
    if(est != nullptr) return est;
    est = buscarEstacion(fila + 1, columna - 1); //esquina inferior izquierda
    if(est != nullptr) return est;
    est = buscarEstacion(fila + 1, columna + 1); //esquina inferior derecha
    if(est != nullptr) return est;
    return nullptr; //si no encuentra ninguna est devuelve nullptr
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

bool Juego::comprobarConexion(int fila, int columna) {
    Estacion* est = estacionCerca(fila, columna);
    if(est != nullptr) {
        Estacion* estInicioDeRuta = estacionCerca(rutasDeRonda[0].first, rutasDeRonda[0].second);
        if(((rutasDeRonda.size() > 0) && (estInicioDeRuta != est)) || ((rutasDeRonda.size() == 1) && (estInicioDeRuta == est) && (cantidadEstacionesCerca(fila, columna) > 1))) {
            return est->comprobaciones(fila, columna);
        }
    }
}

pair<int, int> Juego::getCoordenadasRutaIndice(int indice)
{
    return this->rutasDeRonda[indice];
}

int Juego::getCantidadRutas()
{
    return this->rutasDeRonda.size();
}

int Juego::getCantidadEstaciones()
{
    return this->estaciones.size();
}

bool Juego::ponerRuta(int fila, int columna)
{

    if(sePuedeConectarRuta(fila,columna) && overrideComprobacion)//parche inmundo pero funciona
    {
        this->tablero->setEnPos(fila,columna,5);
        pair<int,int> coordsRuta(fila, columna);
        this->rutasDeRonda.push_back(coordsRuta);
        this->ultimaRuta = coordsRuta;
        this->rutasTotales.push_back(ultimaRuta);
        overrideComprobacion=false;
        return true;
    }


    if(comprobarRuta(fila, columna) && sePuedeConectarRuta(fila, columna)) {
        this->tablero->setEnPos(fila,columna,5);//5 es ruta
        pair<int,int> coordsRuta(fila, columna);
        this->rutasDeRonda.push_back(coordsRuta);
        this->ultimaRuta = coordsRuta;
        this->rutasTotales.push_back(ultimaRuta);
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

void Juego::victoria()
{
    QMessageBox mensaje;

    mensaje.setText("Ganaste!");
    mensaje.setStandardButtons(QMessageBox::Ok);
}

void Juego::setCronometro(Cronometro *c)
{
    this->cronometro = c;
}

int Juego::getSegundosRestantes()
{
    return t.segundosRestantes;
}

int Juego::getSegundosTotales()
{
    return t.segundosTotales;
}

Cronometro *Juego::getReferenciaCronometro()
{
    return this->cronometro;
}

Estacion *Juego::getReferenciaEstacionIndice(int indice)
{
    return this->estaciones[indice];
}

void Juego::guardarPartida()
{
    QFile salida("partida.dat");
    salida.open(QIODevice::WriteOnly);

    //se debe guardar en el siguiente orden, tamaño tablero, cantidad estaciones, cantidad rutas, estaciones, rutas, ultima ruta, tiempo

    if(salida.isOpen()) {

        //TAMAÑO TABLERO, CANTIDAD ESTACIONES, CANTIDAD RUTAS
        cantidades c;
        c.tableroX=getColumnas();
        c.tableroY=getFilas();
        c.cantidadEstaciones = estaciones.size();
        c.cantidadRutas = rutasTotales.size();
        salida.write((char*)&c,sizeof(cantidades));

        //ESTACIONES
        estacion e;
        for(int i=0; i<estaciones.size(); i++) {
            e.tipo = estaciones[i]->getTipo();
            e.posX = estaciones[i]->getX();
            e.posY = estaciones[i]->getY();
            salida.write((char*)&e,sizeof(estacion));
        }

        //RUTAS, ULTIMA RUTA
        ruta r;
        for(int i=0; i<rutasTotales.size(); i++)
        {
            r.ultimaRuta.first = rutasTotales[i].first;
            r.ultimaRuta.second = rutasTotales[i].second;
            salida.write((char*)&r,sizeof(ruta));
        }

        //TIEMPO
        tiempo t;
        t.segundosRestantes=this->getReferenciaCronometro()->getContadorSegundos();
        t.segundosTotales=this->getReferenciaCronometro()->getSegundosEstablecidos();
        salida.write((char*)&t,sizeof(tiempo));

        salida.close();

    }
}

bool Juego::cargarPartida()
{
    QFile entrada("partida.dat");
    entrada.open(QIODevice::ReadOnly);

    if(entrada.isOpen()) {//cargar los datos de cada estacion
        cantidades c;
        ruta r;
        estacion e;
        Estacion* nuevaEstacion;

        entrada.read((char*)&c,sizeof(cantidades));//TAMAÑO TABLERO, CANTIDAD ESTACIONES, CANTIDAD RUTAS

        for(int i=0; i<c.cantidadEstaciones; i++)//ESTACIONES
        {
            entrada.read((char*)&e,sizeof(estacion));
            switch(e.tipo)
            {
                case 1: nuevaEstacion = new Comun(e.posX,e.posY,this->tablero); nuevaEstacion->setTipo(e.tipo); break;
                case 2: nuevaEstacion = new Multiple(e.posX,e.posY,this->tablero); nuevaEstacion->setTipo(e.tipo); break;
                case 3: nuevaEstacion = new Horizontal(e.posX,e.posY,this->tablero); nuevaEstacion->setTipo(e.tipo); break;
                case 4: nuevaEstacion = new Vertical(e.posX,e.posY,this->tablero); nuevaEstacion->setTipo(e.tipo); break;
            }
            estaciones.push_back(nuevaEstacion);
        }


        for(int i=0; i<c.cantidadRutas; i++)
        {
            entrada.read((char*)&r,sizeof(ruta));
            this->ultimaRuta.first = r.ultimaRuta.first;
            this->ultimaRuta.second = r.ultimaRuta.second;
            this->rutasDeRonda.push_back(this->ultimaRuta);
            this->rutasTotales.push_back(this->ultimaRuta);
        }

        entrada.read((char*)&t,sizeof(tiempo));


        entrada.close();

        setFilas(c.tableroY);
        setColumnas(c.tableroX);
        overrideComprobacion=true;
        return true;
    }
    return false;
}



int* Juego::nuevaRonda() {
    this->rutasDeRonda.clear(); //se limpian las rutas de la ronda anterior;
    this->ronda++;
    //poner nueva estacion
    int* coords = this->ponerEstacion();
    return coords;
}

bool Juego::validezEstacion(int fila, int columna, int tipo)//corroborar que la posicion de estacion sea valida
{
    if(tipo == 1 || tipo == 2)
    {
        if(this->tablero->getEnPos(fila,columna)!=0)
        {
            return false;
        }
    }
    else if(tipo == 3)
    {
        if((columna == 0) || (columna == this->columnas - 1) || (this->tablero->getEnPos(fila,columna) != 0))
        {
            return false;
        }
    }
    else if(tipo == 4)
    {
        if((fila == 0) || (fila == this->filas - 1) || (this->tablero->getEnPos(fila,columna)!=0))
        {
            return false;
        }
    }
    return true;
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
