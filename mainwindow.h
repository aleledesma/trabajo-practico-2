#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QPushButton>
#include <QGridLayout>
#include "juego.h"
#include "cronometro.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void cargarConfiguracion();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Juego* juego = nullptr;
    QFrame* frameGameScreen = nullptr;
    QGridLayout* gridLayout = nullptr;
    QPushButton*** matrizBotones = nullptr;
    Cronometro* cronometro = nullptr;
    QTimer* timer = nullptr;

private slots:
    void onTimer();
};
#endif // MAINWINDOW_H
