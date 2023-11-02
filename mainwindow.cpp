#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablero.h"
#include "juego.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //valores minimos ej: 10 filas/columnas
    this->ui->spinBox->setMinimum(10);
    this->ui->spinBox_2->setMinimum(10);
    //valores maximos ej: 50 filas/columnas
    this->ui->spinBox->setMaximum(50);
    this->ui->spinBox_2->setMaximum(50);
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

void MainWindow::on_pushButton_clicked()
{
    int filas = this->ui->spinBox->value();
    int columnas = this->ui->spinBox_2->value();

    this->frameGameScreen = new QFrame(this);
    this->gridLayout = new QGridLayout(frameGameScreen);
    this->adjustSize(); //ajusta el tamaño al mínimo requerido

    this->juego = new Juego(filas, columnas);
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
                                      this->matrizBotones[i][j]->setText("v");
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

    int** posiciones = this->juego->iniciarJuego(1);

    //Todo esto hay que sacarlo de aca y hacerlo reutilizable para cada estacion que se coloque, porque esto solo funciona para las 2 primeras estaciones que se creen
    int tipoEstacion = juego->getReferenciaEstacionIndice(0)->getTipo();//aca sacamos el tipo de estacion de adentro del vector
    QString c;
    c.setNum(tipoEstacion);//aca lo convertimos de int a QString

    this->matrizBotones[posiciones[0][0]][posiciones[0][1]]->setText(c);//aca lo mostramos en el tablero, despues le ponemos una fotito en base al numero

    tipoEstacion = juego->getReferenciaEstacionIndice(1)->getTipo();
    c.setNum(tipoEstacion);

    this->matrizBotones[posiciones[1][0]][posiciones[1][1]]->setText(c);

}

void MainWindow::on_pushButton_3_clicked()
{
    this->juego = new Juego();
    if(this->juego->cargarPartida())
    {
        this->frameGameScreen = new QFrame(this);
        this->gridLayout = new QGridLayout(frameGameScreen);
        this->adjustSize();

        this->juego->cargarPartida();
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
                                        this->matrizBotones[i][j]->setText("v");
                                        this->juego->guardarPartida();
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

            QString c;
            c.setNum(tipoEstacion);

            this->matrizBotones[x][y]->setText(c);
        }
        for(int i=0; i<this->juego->getCantidadRutas(); i++)
        {
            pair<int,int> coordenadas;
            coordenadas = juego->getCoordenadasRutaIndice(i);

            this->matrizBotones[coordenadas.first][coordenadas.second]->setText("v");//esto hay que cambiarlo para que tome el tipo de ruta
        }
    }
}
