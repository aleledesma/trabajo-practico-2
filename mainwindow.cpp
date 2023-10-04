#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    this->matrizBotones = new QPushButton**[filas];
    for(int i = 0; i<filas; i++) {
        this->matrizBotones[i] = new QPushButton*[columnas];
        for(int j = 0; j<columnas; j++) {
            this->matrizBotones[i][j] = new QPushButton(this);
            this->matrizBotones[i][j]->setFixedSize(50,50);
            this->gridLayout->addWidget(this->matrizBotones[i][j], i, j);
        }
    }
    this->frameGameScreen->setLayout(this->gridLayout);
    //
    this->setCentralWidget(frameGameScreen); //al poner el frame del juego como "central widget" se reemplaza/oculta el frame de configuración

    this->juego = new Juego(filas, columnas);
    int** posiciones = this->juego->iniciarJuego(1);
    this->matrizBotones[posiciones[0][0]][posiciones[0][1]]->setText("c");
    this->matrizBotones[posiciones[1][0]][posiciones[1][1]]->setText("c");
   // this->matrizBotones[0][0]->setText("🚉");
    //this->matrizBotones[1][1]->setText("🚉");

}

