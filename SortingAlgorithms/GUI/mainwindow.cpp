//includes proprios
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MntDataBase.h"
#include "Ordenation.h"
#include "PaintGraphic.h"
#include "DataBase/Connection/ConnectionDb.h"
#include "Exceptions/Exception.h"
#include "Util/ShowError.h"

//includes Qt
#include <QMovie>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>

//includes C++
#include <iostream>
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(nullptr));
    setGifs();

    try {
        ConnectionDb::open("../Data/statistics.db", "QSQLITE");
    } catch (Exception e) {
        ShowError::error(e.getError());
    }

    setWindowTitle("Sorting Algorithms");
    showMaximized();
}

MainWindow::~MainWindow()
{
    //liberando as memorias alocadas
    delete ui;
    for(int i = 0; i < 6; i++)
        delete vetMovie[i];
    delete [] vetMovie;
}

void MainWindow::setGifs()
{
    //fixando as alturas
    ui->widgetGifs->setFixedHeight(130);
    ui->widgetText->setFixedHeight(40);
    ui->label_textInsertion->setFixedHeight(25);
    ui->label_textSelection->setFixedHeight(25);
    ui->label_textBubble->setFixedHeight(25);
    ui->label_textMerge->setFixedHeight(25);
    ui->label_textQuick->setFixedHeight(25);
    ui->label_textHeap->setFixedHeight(25);

    //carregando os gifs em memoria e setando para o label
    vetMovie = new QMovie *[6];
    vetMovie[0] = new QMovie(":/gifs/Images/gifs/insertion.gif");
    vetMovie[1] = new QMovie(":/gifs/Images/gifs/selection.gif");
    vetMovie[2] = new QMovie(":/gifs/Images/gifs/bubble.gif");
    vetMovie[3] = new QMovie(":/gifs/Images/gifs/merge.gif");
    vetMovie[4] = new QMovie(":/gifs/Images/gifs/quick.gif");
    vetMovie[5] = new QMovie(":/gifs/Images/gifs/heap.gif");
    ui->labelInsertion->setMovie(vetMovie[0]);
    ui->labelSelection->setMovie(vetMovie[1]);
    ui->labelBubble->setMovie(vetMovie[2]);
    ui->labelMerge->setMovie(vetMovie[3]);
    ui->labelQuick->setMovie(vetMovie[4]);
    ui->labelHeap->setMovie(vetMovie[5]);

    //startando os gifs
    startGifs();

    //definindo uma restatação
    timer = new QTimer(this);
    timer->setInterval(5000);
    connect(timer, SIGNAL(timeout()), this, SLOT(startGifs()));
    timer->start();
}

void MainWindow::startGifs()
{
    for(int i = 0; i < 6; i++)
        vetMovie[i]->start();
}

void MainWindow::on_action_New_odenation_triggered()
{
    Ordenation::showForm(this);
}

void MainWindow::on_actionGraph_triggered()
{
    if (!ConnectionDb::isConnected())
        ShowError::error("Banco de dados não foi carregado.");
    else PaintGraphic::showForm(this);
}

void MainWindow::on_action_Data_base_triggered()
{
    if (!ConnectionDb::isConnected())
        ShowError::error("Banco de dados não foi carregado.");
    else MntDataBase::showForm(this);
}
