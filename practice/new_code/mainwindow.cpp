#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRgb>
#include "scene.h"
#include "timer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->setGeometry(0,0,800,600);
    ui->widget->setFixedSize(1000, 800);
    ui->widget->geometry().center();
    canvas = new Drawer(ui->widget);
    this->setWindowTitle("Практика 2022");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_1_clicked()
{
    Scene *sc = new Scene(canvas);
    cur_image = sc->draw_scene_1();
    cur_image.save("img.png");
}


void MainWindow::on_pushButton_2_clicked()
{
    Scene *sc = new Scene(canvas);
    cur_image = sc->draw_scene_2();
    cur_image.save("img.png");
}


void MainWindow::on_pushButton_3_clicked()
{
    Scene *sc = new Scene(canvas);
    cur_image = sc->draw_scene_3();
    cur_image.save("img.png");
}


void MainWindow::on_pushButton_clicked()
{
    Timer t(500);
    t.calculate_time();
    system("python graphics.py");
}

