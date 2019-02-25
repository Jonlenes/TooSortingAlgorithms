//includes proprios
#include "PaintGraphic.h"
#include "ui_PaintGraphic.h"
#include "DataBase/Dao/DAOOrdenation.h"
#include "PopUp.h"
#include "DataBase/Connection/ConnectionDb.h"
#include "Util/Web.h"
#include "Util/ShowError.h"

//includes c++
#include <QPainter>
#include <fstream>
#include <list>

using namespace std;

PaintGraphic *PaintGraphic::frm = 0;

PaintGraphic::PaintGraphic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintGraphic)
{
    ui->setupUi(this);
    setWindowFlags(parent->windowFlags());
    widgetGraphic = nullptr;
    initFilter();
    widgetGraphic = new WidPaintGraphic(parent);
    initGUI();
}

PaintGraphic::~PaintGraphic()
{
    delete ui;
}

void PaintGraphic::showForm(QWidget *parent)
{
    if (!frm)
        frm = new PaintGraphic(parent);
    else
        frm->setParent(parent);
    if(parent) frm->setWindowFlags(parent->windowFlags());
    frm->showMaximized();
}

void PaintGraphic::closeEvent(QCloseEvent *)
{
    delete frm;
    frm = nullptr;
}

void PaintGraphic::on_comboBoxOrder_activated(int index)
{
    ordem = index;
    applyFilter();
}

void PaintGraphic::on_pushButtonFilterAlgo_clicked()
{
    PopUp::showPopUp(this, listAlgo, listFilterAlgo, "Selecione os algoritmos desejados");
    applyFilter();
}

void PaintGraphic::on_pushButtonFiltrarSize_clicked()
{
    PopUp::showPopUp(this, listSize, listFilterSize, "Selecione os tamanhos desejados");
    applyFilter();
}

void PaintGraphic::on_comboBoxAlgoritmoTabela_activated(const QString &arg1)
{
    preencheWidgetTable(arg1);
}

void PaintGraphic::initGUI()
{
    ui->verticalLayoutPaintGraphic->addWidget(widgetGraphic);
    ui->tableWidgetValues->setFixedHeight(80);
    ui->groupBoxLegenda->setFixedHeight(30);

    ui->groupBoxParametrosGrafico->setFixedHeight(50);
    ui->groupBoxParametrosTabela->setFixedHeight(50);
    ui->groupBoxWeb->setFixedHeight(50);
    ui->groupBoxParametrosGrafico->setFixedWidth(700);

    ui->comboBoxOrder->setFixedWidth(130);
    ui->labelOrder->setFixedWidth(110);
    ui->pushButtonFilterAlgo->setFixedWidth(200);
    ui->pushButtonFiltrarSize->setFixedWidth(200);
    ui->pushButtonGeraViewWeb->setFixedWidth(200);
    ui->comboBoxOrder->setFixedHeight(20);
    ui->pushButtonFilterAlgo->setFixedHeight(20);
    ui->pushButtonFiltrarSize->setFixedHeight(20);
    ui->pushButtonGeraViewWeb->setFixedHeight(20);

    ui->labelCaptionTabela->setFixedHeight(20);
    ui->labelCaptionTabela->setAlignment(Qt::AlignCenter);
    ui->comboBoxOrder->setFocus();

    setWindowTitle("Graphic and Tables");
}

void PaintGraphic::fillComboAlgo()
{
    ui->comboBoxAlgoritmoTabela->clear();
    ui->comboBoxAlgoritmoTabela->addItems(listFilterAlgo);
    preencheWidgetTable(ui->comboBoxAlgoritmoTabela->currentText());
}

void PaintGraphic::initFilter()
{
    DAOOrdenation::clearFilter();

    ordem = 0;
    listAlgo = DAOOrdenation::getAlgorithms();
    list<long long> listSize = DAOOrdenation::getSizes();
    for (auto i : listSize) {
        this->listSize.append(QString::number(i));
    }
    listFilterAlgo = listAlgo;
    listFilterSize = this->listSize;

    applyFilter();
}

void PaintGraphic::applyFilter()
{
    DAOOrdenation::setFilter(ordem, listFilterAlgo, listFilterSize);
    if (widgetGraphic) widgetGraphic->repaint();
    fillComboAlgo();
}

void PaintGraphic::preencheWidgetTable(QString strAlgo)
{
    list<long long> listSize = DAOOrdenation::getSizes(strAlgo);
    list<MOrdenation> listMedium = DAOOrdenation::mediumTime(strAlgo);

    //limpando o grid
    ui->tableWidgetValues->clear();
    ui->tableWidgetValues->setColumnCount(0);
    ui->tableWidgetValues->setRowCount(0);
    ui->tableWidgetValues->setColumnCount(listSize.size() + 1);
    ui->tableWidgetValues->setRowCount(1);

    //Montando o cabeçalho do grid
    ui->tableWidgetValues->setRowHeight(0, 18);
    QTableWidgetItem *item = new QTableWidgetItem(QString("Qtde de elementos"));
    ui->tableWidgetValues->setHorizontalHeaderItem(0, item);
    ui->tableWidgetValues->setColumnWidth(0, 200);

    //colocando os tamanhos no cabecacho do grid
    int i = 1;
    for(auto itemList : listSize)
    {
        item = new QTableWidgetItem(QString::number(itemList));
        ui->tableWidgetValues->setHorizontalHeaderItem(i, item);
        i++;
    }

    //formatando o item com o nome do algoritmo
    ui->tableWidgetValues->setRowHeight(1, 18);
    item = new QTableWidgetItem(strAlgo + "Sort (Média de tempo)");
    item->setTextColor(Qt::black);
    item->setFont(QFont("Arial", 8, QFont::Bold));
    item->setBackgroundColor(QColor("#A9BCF5"));
    ui->tableWidgetValues->setItem(0, 0, item);


    //inserindo os tempos
    i = 1;
    for(auto item : listMedium )
    {
        ui->tableWidgetValues->setItem(0, i, new QTableWidgetItem(QString::number(static_cast<MOrdenation> (item).getTime())));
        i++;
    }
}

void PaintGraphic::on_pushButtonGeraViewWeb_clicked()
{
    for (int i = 0; i < 3; i++)
        widgetGraphic->printMeAll(i);
    Web::generetareHtml(widgetGraphic->getMyMap());
    initFilter();

    ShowError::error("Caso ocorra erro de endereço devedo a caraters especiais,"
                     "abra ProjectOrdenation/SortingAlgorithms/projetoWeb/OrdenationWeb.\n"
                     "Se o seu navegador padrão não for o chrome pode ocorrer alguns erros em funções javaScript.\n", true);
}
