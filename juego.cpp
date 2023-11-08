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
    //iniciar cronometro
    int** posiciones = new int*[2];
    for(int i = 0; i<2; i++) {
        posiciones[i] = new int[2];
        //nota: el metodo ponerEstacion es quien deberia generar las posiciones fila y columna en donde colocar la estación, ya que desde ahi podemos contemplar los distintos casos (por ejemplo que las estaciones verticales no esten pegadas a los bordes, etc)
        int fila = this->genNumero(this->filas);//fantastica idea, no hay tiempo para implementarla
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

void Juego::ponerEstacion(int fila, int columna)
{
    bool colocada=false;
    int tipoEstacion;
    for(int i=0; i<1000; i++)//si despues de 1000 iteraciones no encuentra una posicion valida, tomarlo como victoria
    {
        tipoEstacion = rand() % 4+1;
        if(!validezEstacion(fila,columna,tipoEstacion))
        {
            fila = rand()%this->filas;
            columnas = rand()%this->columnas;
            colocada=false;
        }
        else
        {
            colocada=true;
            i=1000;
        }
    }
    if(!colocada)
    {
        victoria();
        return;
    }

    if(fila < this->filas && columna < this->columnas) {
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
}//dale maquina, gracias por la explicacion

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
        if(this->rutasDeRonda.size() > 1) {
            if(est->comprobaciones(fila, columna)) {
                cout<<"estacion conectada!"<<endl;
                return true;
            }
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

        Estacion* est = estacionCerca(fila, columna);
        if(est != nullptr) {
            if(this->rutasDeRonda.size() > 1) {
                if(est->comprobaciones(fila, columna)) {
                    cout<<"Estacion conectada"<<endl;
                }
            }
        }
        overrideComprobacion=false;
        return true;
    }


    if(comprobarRuta(fila, columna) && sePuedeConectarRuta(fila, columna)) {
        this->tablero->setEnPos(fila,columna,5);//5 es ruta
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

    //se debe guardar en el siguiente orden, tamaño tablero, cantidad estaciones, cantidad rutas, estaciones, rutas, ultima ruta

    if(salida.isOpen()) {

        //TAMAÑO TABLERO, CANTIDAD ESTACIONES, CANTIDAD RUTAS
        cantidades c;
        c.tableroX=getColumnas();
        c.tableroY=getFilas();
        c.cantidadEstaciones = estaciones.size();
        c.cantidadRutas = rutasDeRonda.size();
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
        for(int i=0; i<rutasDeRonda.size(); i++)
        {
            r.ultimaRuta.first = rutasDeRonda[i].first;
            r.ultimaRuta.second = rutasDeRonda[i].second;
            salida.write((char*)&r,sizeof(ruta));
        }

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
    int fila;
    int columna;
    do {
        fila = genNumero(this->filas);
        columna = genNumero(this->columnas);
    } while(this->tablero->getEnPos(fila, columna) != 0 && estacionCerca(fila,columna)!=nullptr);
    this->ponerEstacion(fila, columna);
    int* coords = new int[2];
    coords[0] = fila;
    coords[1] = columna;
    return coords;
}

bool Juego::validezEstacion(int fila, int columna, int tipo)//corroborar que la posicion de estacion sea valida
{
    if(tipo==1 || tipo==2)
    {
        if(this->tablero->getEnPos(fila,columna)!=0)
        {
            return false;
        }
    }
    if(tipo==3)
    {
        if(columna==0 || columna==this->columnas-1 || this->tablero->getEnPos(fila,columna)!=0)
        {
            return false;
        }
    }
    if(tipo==4)
    {
        if(fila==0 || fila==this->filas-1 || this->tablero->getEnPos(fila,columna)!=0)
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
