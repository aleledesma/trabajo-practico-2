#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablero.h"
#include "juego.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Juego de trenes");
    //valores minimos
    this->ui->spinBox->setMinimum(10); //min filas
    this->ui->spinBox_2->setMinimum(10); //min columnas
    this->ui->spinBox_3->setMinimum(15); //min 15seg
    //valores maximos
    this->ui->spinBox->setMaximum(50); //max filas
    this->ui->spinBox_2->setMaximum(50); //max columnas
    this->ui->spinBox_3->setMaximum(60); //max 60seg
    cargarConfiguracion();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->juego;
    delete this->frameGameScreen;
    delete this->gridLayout;
    for(int i = 0; i<this->juego->getFilas(); i++) {
        for(int j = 0; j<this->juego->getColumnas(); j++) {
            delete this->matrizBotones[i][j];
        }
        delete[] this->matrizBotones[i];
    }
    delete[] matrizBotones;
}

QString devolverTipoEstacion(int t)
{
    QString c;

    switch (t) {
           case 1: c="C"; break;
           case 2: c="M"; break;
           case 3: c="H"; break;
           case 4: c="V"; break;
           default: break;
    }

    return c;
}

void MainWindow::on_pushButton_clicked()
{
    int filas = this->ui->spinBox->value();
    int columnas = this->ui->spinBox_2->value();
    int segundos = this->ui->spinBox_3->value();
    this->cronometro = new Cronometro(segundos);
    this->timer = new QTimer;
    this->timer->setInterval(1000); //intervalo de 1seg
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimer()));

    this->frameGameScreen = new QFrame(this);
    this->gridLayout = new QGridLayout(frameGameScreen);
    this->adjustSize(); //ajusta el tamaño al mínimo requerido

    this->juego = new Juego(filas, columnas);
    this->juego->setCronometro(cronometro);
    this->matrizBotones = new QPushButton**[filas];
    for(int i = 0; i<filas; i++) {
        this->matrizBotones[i] = new QPushButton*[columnas];
        for(int j = 0; j<columnas; j++) {
            this->matrizBotones[i][j] = new QPushButton(this);
            this->matrizBotones[i][j]->setFixedSize(50,50);
            this->gridLayout->addWidget(this->matrizBotones[i][j], i, j);
            //
            QObject::connect(this->matrizBotones[i][j],
                             &QPushButton::clicked,
                             [=](){
                                 bool res = juego->ponerRuta(i, j);
                                 if(res) {
                                     this->matrizBotones[i][j]->setStyleSheet("QPushButton { background-color: grey; }\n""QPushButton:enabled { background-color: rgb(180,180,180); }\n");
                                     this->matrizBotones[i][j]->setText("*");
                                     if(this->juego->comprobarConexion(i, j)) {
                                         this->cronometro->reiniciar();
                                         int* nuevaEstacionCoords = this->juego->nuevaRonda();
                                         int tipoEstacion = juego->getReferenciaEstacionIndice(this->juego->getCantidadEstaciones() - 1)->getTipo();

                                         this->matrizBotones[nuevaEstacionCoords[0]][nuevaEstacionCoords[1]]->setText(devolverTipoEstacion(tipoEstacion));
                                         this->matrizBotones[nuevaEstacionCoords[0]][nuevaEstacionCoords[1]]->setStyleSheet("QPushButton { background-color: grey; }\n""QPushButton:enabled { background-color: rgb(100,180,100); }\n");
                                     }
                                     //juego->comprobarConexionEstaciones();//cada vez que hacemos click, se comprueba si las estaciones estan conectadas
                                     this->juego->guardarPartida();
                                 }
                             }
            );
        }
    }

    this->frameGameScreen->setLayout(this->gridLayout);
    //
    this->setCentralWidget(frameGameScreen); //al poner el frame del juego como "central widget" se reemplaza/oculta el frame de configuración

    int** posiciones = this->juego->iniciarJuego();
    this->setWindowTitle("Segundos restantes: " + QString::number(segundos));
    this->timer->start();

    //Todo esto hay que sacarlo de aca y hacerlo reutilizable para cada estacion que se coloque, porque esto solo funciona para las 2 primeras estaciones que se creen
    int tipoEstacion = juego->getReferenciaEstacionIndice(0)->getTipo();//aca sacamos el tipo de estacion de adentro del vector

    this->matrizBotones[posiciones[0][0]][posiciones[0][1]]->setText(devolverTipoEstacion(tipoEstacion));//aca lo mostramos en el tablero, despues le ponemos una fotito en base al numero
    this->matrizBotones[posiciones[0][0]][posiciones[0][1]]->setStyleSheet("QPushButton { background-color: grey; }\n""QPushButton:enabled { background-color: rgb(100,180,100); }\n");

    tipoEstacion = juego->getReferenciaEstacionIndice(1)->getTipo();

    this->matrizBotones[posiciones[1][0]][posiciones[1][1]]->setText(devolverTipoEstacion(tipoEstacion));
    this->matrizBotones[posiciones[1][0]][posiciones[1][1]]->setStyleSheet("QPushButton { background-color: grey; }\n""QPushButton:enabled { background-color: rgb(100,180,100); }\n");


}

void MainWindow::on_pushButton_3_clicked()//todo esto hay que cambiarlo porque nos van a meter un 0
{
    this->juego = new Juego();

    if(this->juego->cargarPartida())
    {
        this->frameGameScreen = new QFrame(this);
        this->gridLayout = new QGridLayout(frameGameScreen);
        this->adjustSize();

        this->cronometro = new Cronometro;

        this->timer = new QTimer;
        this->timer->setInterval(1000); //intervalo de 1seg
        QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(onTimer()));

        this->juego->setCronometro(cronometro);

        this->juego->cargarPartida();

        this->juego->getReferenciaCronometro()->setContadorSegundos(this->juego->getSegundosRestantes());
        this->juego->getReferenciaCronometro()->setSegundosEstablecidos(this->juego->getSegundosTotales());

        this->juego->instanciarTablero();

        this->matrizBotones = new QPushButton**[this->juego->getFilas()];
        for(int i = 0; i<this->juego->getFilas(); i++) {
            this->matrizBotones[i] = new QPushButton*[this->juego->getColumnas()];
            for(int j = 0; j<this->juego->getColumnas(); j++) {
                this->matrizBotones[i][j] = new QPushButton(this);
                this->matrizBotones[i][j]->setFixedSize(50,50);
                this->gridLayout->addWidget(this->matrizBotones[i][j], i, j);
                //
                QObject::connect(this->matrizBotones[i][j],
                                 &QPushButton::clicked,
                                 [=](){
                                    bool res = juego->ponerRuta(i, j);
                                    if(res) {
                                        this->matrizBotones[i][j]->setStyleSheet("QPushButton { background-color: grey; }\n""QPushButton:enabled { background-color: rgb(180,180,180); }\n");
                                        this->matrizBotones[i][j]->setText("*");
                                        if(this->juego->comprobarConexion(i, j)) {
                                        this->cronometro->reiniciar();
                                        int* nuevaEstacionCoords = this->juego->nuevaRonda();
                                        int tipoEstacion = juego->getReferenciaEstacionIndice(this->juego->getCantidadEstaciones() - 1)->getTipo();

                                        this->matrizBotones[nuevaEstacionCoords[0]][nuevaEstacionCoords[1]]->setText(devolverTipoEstacion(tipoEstacion));
                                        this->matrizBotones[nuevaEstacionCoords[0]][nuevaEstacionCoords[1]]->setStyleSheet("QPushButton { background-color: grey; }\n""QPushButton:enabled { background-color: rgb(100,180,100); }\n");
                                        }
                                        this->juego->guardarPartida();
                                    }
                                   }
                );
            }
        }

        this->frameGameScreen->setLayout(this->gridLayout);
        //
        this->setCentralWidget(frameGameScreen); //al poner el frame del juego como "central widget" se reemplaza/oculta el frame de configuración

        for(int i=0; i<this->juego->getCantidadEstaciones(); i++)
        {
            int x = juego->getReferenciaEstacionIndice(i)->getX();
            int y = juego->getReferenciaEstacionIndice(i)->getY();
            int tipoEstacion = juego->getReferenciaEstacionIndice(i)->getTipo();

            this->matrizBotones[x][y]->setText(devolverTipoEstacion(tipoEstacion));
            this->matrizBotones[x][y]->setStyleSheet("QPushButton { background-color: grey; }\n""QPushButton:enabled { background-color: rgb(100,180,100); }\n");
        }
        for(int i=0; i<this->juego->getCantidadRutas(); i++)
        {
            pair<int,int> coordenadas;
            coordenadas = juego->getCoordenadasRutaIndice(i);

            this->matrizBotones[coordenadas.first][coordenadas.second]->setText("*");
            this->matrizBotones[coordenadas.first][coordenadas.second]->setStyleSheet("QPushButton { background-color: grey; }\n""QPushButton:enabled { background-color: rgb(180,180,180); }\n");
        }
        int** posiciones = this->juego->iniciarJuego();
        this->setWindowTitle("Segundos restantes: " + QString::number(this->juego->getReferenciaCronometro()->getContadorSegundos()));
        this->timer->start();
    }
}

void MainWindow::onTimer()
{
    this->cronometro->decrementar();
    this->setWindowTitle("Segundos restantes: " + QString::number(this->cronometro->getContadorSegundos()));

    //si se pierde
    if(this->cronometro->getContadorSegundos() == 0) {
        QMessageBox mensaje;
        mensaje.setText("Perdiste!");
        mensaje.setStandardButtons(QMessageBox::Ok);
        this->timer->stop();
        this->setWindowTitle("Perdiste!");
        int btnRes = mensaje.exec();
        if(btnRes == QMessageBox::Ok) {
            this->close();
        }
    }
}

void MainWindow::cargarConfiguracion()
{
    int f;
    int c;
    int s;
    QFile entrada("config.txt");
    if(!entrada.exists())
    {
        entrada.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream ent(&entrada);
        ent<<10<<"\n"<<10<<"\n"<<15<<"\n";
        entrada.close();
    }
    else
    {
        entrada.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream ent(&entrada);
        QString str;
        str = ent.readLine();
        f=str.toInt();
        str = ent.readLine();
        c=str.toInt();
        str = ent.readLine();
        s=str.toInt();

        this->ui->spinBox->setValue(f);
        this->ui->spinBox_2->setValue(c);
        this->ui->spinBox_3->setValue(s);

        entrada.close();
    }
}

