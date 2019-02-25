//includes proprios
#include "Ordenation.h"
#include "ui_Ordenation.h"
#include "Enums.h"
#include "Util/GenerateVector.h"
#include "Util/TimeMeter.h"
#include "Sort/Sort.h"
#include "Util/ShowError.h"
#include "DataBase/Dao/DAOOrdenation.h"
#include "GUI/PopUp.h"
#include "DataBase/Connection/ConnectionDb.h"
#include "Util/ShowError.h"

//includes Qt
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>

//includes c++
#include <algorithm>
#include <fstream>

using namespace std;

//defines
#define vQtde  ui->lineEditQtdeEle->text().toLongLong()
#define vBegin ui->lineEditValueBegin->text().toLongLong()

Ordenation *Ordenation::frm = 0;

Ordenation::Ordenation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ordenation)
{
    ui->setupUi(this);
    initGUI();
}

Ordenation::~Ordenation()
{
    delete ui;
    delete labStatus;
    delete prbStatus;
    for(int i = 0; i <= countAlgo; i++)
        delete [] vectors[i];
    delete [] vectors;
    delete [] vetOrdenation;
}

void Ordenation::showForm(QWidget *parent)
{
    if (!frm)
        frm = new Ordenation(parent);
    else
        frm->setParent(parent);
    if(parent) frm->setWindowFlags(parent->windowFlags());
    frm->showMaximized();
}

void Ordenation::closeEvent(QCloseEvent *)
{
    delete frm;
    frm = nullptr;
}

void Ordenation::on_pushButtonGerar_clicked()
{
    try {
        if (vQtde > 0) {
            resetTable();
            sizeVector = vQtde;
            GenerateVector::all(vectors[0], vQtde, order, vBegin);
            addColumnGridVectores(IndexVector::Original);
        } else
            ShowError::error("Tamanho não informado.");
    } catch (string e) {
        ShowError::error(e);
    }
}

void Ordenation::on_comboBoxOrder_activated(int index)
{
    order = Order(index);
    ui->lineEditValueBegin->setEnabled(index != 2);
}

void Ordenation::on_pushButtonOrdenar_clicked()
{
    if(vectors[static_cast<int> (IndexVector::Original)]) {
        callOrdenation();
    } else
        ShowError::error("Vetor não foi carragado/gerado.");
}

void Ordenation::on_radioButtonInCarregar_clicked()
{
    try{
        setStatus(-1, "Lendo .txt...");
        QString path = QFileDialog::getOpenFileName(this, "Abrir - Numeros separados por espaço ou enter", "", "Arquivo de texto(*.txt)");

        fstream *file = new fstream(path.toStdString().c_str());
        if(file->is_open())
        {
            sizeVector = QInputDialog::getInt(this, "Tamanho do vetor", "");
            vectors[0] = new long long[sizeVector];
            for(int i = 0; i < sizeVector; i++)
                *file >> vectors[0][i];
            addColumnGridVectores(IndexVector::Original);
            setStatus(-1, "Pronto...");
        }
        else
            ShowError::error("Erro no endereço do arquivo.");
        file->close();
    } catch(...) {
        ShowError::error("Erro! Arquivo inválido.");
        if(vectors[0]) delete vectors[0];
        sizeVector = -1;
    }

    ui->radioButtonInGerar->setChecked(true);
    setStatus(-1, "Pronto...");
}

void Ordenation::on_pushButtonAlgoritmos_clicked()
{
    QString result = PopUp::showPopUp(this, listAlgoritmos, listAlgoritmosSelected, "Selecione os algoritmos desejados");
    ui->pushButtonAlgoritmos->setText(result);
}








void Ordenation::initGUI()
{
    connect(ui->radioButtonInGerar, SIGNAL(toggled(bool)), ui->comboBoxOrder, SLOT(setEnabled(bool)));
    connect(ui->radioButtonInGerar, SIGNAL(toggled(bool)), ui->lineEditQtdeEle, SLOT(setEnabled(bool)));
    connect(ui->radioButtonInGerar, SIGNAL(toggled(bool)), ui->lineEditValueBegin, SLOT(setEnabled(bool)));
    connect(ui->radioButtonInGerar, SIGNAL(toggled(bool)), ui->pushButtonGerar, SLOT(setEnabled(bool)));

    ui->lineEditQtdeEle->setValidator(new QIntValidator);
    ui->lineEditValueBegin->setValidator(new QIntValidator);

    labStatus = new QLabel(this);
    prbStatus = new QProgressBar(this);
    statusBar = new QStatusBar(this);

    ui->labelVetores->setAlignment(Qt::AlignCenter);
    ui->labelTempo->setAlignment(Qt::AlignCenter);
    ui->labelLogs->setAlignment(Qt::AlignCenter);

    ui->radioButtonInGerar->setChecked(true);
    ui->verticalLayoutScreen->addWidget(statusBar);
    ui->labelLogs->setFixedHeight(14);
    statusBar->addPermanentWidget(labStatus, 1);
    statusBar->addPermanentWidget(prbStatus, 1);
    ui->widgetInicio->setFixedHeight(75);
    ui->tableWidgetAlgoXTemp->setFixedWidth(400);
    ui->textEditLog->setFixedHeight(150);
    prbStatus->setRange(0, 100);
    labStatus->setText("Pronto.");

    order = Order::Crescent;
    sizeVector = 0;

    initializesVectors();
    setWindowTitle("Ordination");
}

void Ordenation::initializesVectors()
{
    vectors = new long long *[countAlgo + 1];
    for(int i = 0; i <= countAlgo; i++)
        vectors[i] = nullptr;

    vetOrdenation = new MOrdenation[countAlgo + 1];
    vetOrdenation[IndexVector::Original].setAlgorithm("Original");
    vetOrdenation[IndexVector::Selection].setAlgorithm("Selection");
    vetOrdenation[IndexVector::Insertion].setAlgorithm("Insertion");
    vetOrdenation[IndexVector::Bubble].setAlgorithm("Bubble");
    vetOrdenation[IndexVector::Merge].setAlgorithm("Merge");
    vetOrdenation[IndexVector::Quick].setAlgorithm("Quick");
    vetOrdenation[IndexVector::Heap].setAlgorithm("Heap");

    for (int i = 1; i <= countAlgo; i++) {
        listAlgoritmos.append(vetOrdenation[i].getAlgorithm());
        mapAlgo.insert(i, vetOrdenation[i].getAlgorithm());
    }
    listAlgoritmosSelected = listAlgoritmos;
}

void Ordenation::setStatus(int porct, QString status)
{
    if(status == "-1")
        prbStatus->setValue(porct);
    else
    {
        labStatus->setText(status);
        if(porct == -1)
            prbStatus->reset();
        else
            prbStatus->setValue(porct);
        if(!status.isEmpty()) ui->textEditLog->setText(ui->textEditLog->toPlainText() + "\n" + status);
    }
}

void Ordenation::addColumnGridVectores(IndexVector indexVector)
{
    try {
        if(indexVector == IndexVector::Original)
        {
            setStatus(0, "Preparando grid...");
            ui->tableWidgetVectores->setRowCount(sizeVector);
        }

        ui->tableWidgetVectores->insertColumn(ui->tableWidgetVectores->columnCount());
        ui->tableWidgetVectores->setHorizontalHeaderItem(ui->tableWidgetVectores->columnCount() - 1,
                                                         new QTableWidgetItem(vetOrdenation[indexVector].getAlgorithm()));

        setStatus(0, "Preenchendo vetor " + vetOrdenation[indexVector].getAlgorithm() + " na tabela...");
        for(int i = 0; i < sizeVector; i++)
        {
            ui->tableWidgetVectores->setItem(i, ui->tableWidgetVectores->columnCount() - 1,
                                             new QTableWidgetItem(QString::number(vectors[indexVector][i])));
            setStatus((double) (i/sizeVector) * 100);
        }
        setStatus(-1, "Pronto...");
    } catch (std::bad_alloc) {
        ShowError::error("Memória insuficiente.");
    }
}

void Ordenation::callOrdenation()
{
    for(int i = 1; i <= countAlgo; i++) {
        if (vectors[i]) delete vectors[i];
        vectors[i] = new long long [sizeVector];
        std::copy(vectors[IndexVector::Original ],
                vectors[IndexVector::Original ] + sizeVector,
                vectors[i]);
    }

    foreach (QString item , listAlgoritmosSelected) {
        int i = mapAlgo.key(item);
        setStatus(50, "Executando " + vetOrdenation[i].getAlgorithm() + "Sort...");
        TimeMeter::begin();
        switch (IndexVector(i)) {
        case IndexVector::Selection:
            selectionSort(vectors[i], sizeVector);
            break;
        case IndexVector::Insertion:
            insertionSort(vectors[i], sizeVector);
            break;
        case IndexVector::Bubble:
            bubbleSort(vectors[i], sizeVector);
            break;
        case IndexVector::Merge:
            mergeSort(vectors[i], sizeVector);
            break;
        case IndexVector::Quick:
            quickSort(vectors[i], sizeVector);
            break;
        case IndexVector::Heap:
            heapSort(vectors[i], sizeVector);
            break;
        default:
            break;
        }

        TimeMeter::end();
        vetOrdenation[i].setTime(TimeMeter::diffTime());
        addColumnGridVectores(IndexVector(i));
    }

    setGridTimes();

    if (ConnectionDb::isConnected()) {
        setStatus(-1, "Inserindo dados no banco...");
        foreach (QString item , listAlgoritmosSelected) {
            int i = mapAlgo.key(item);
            vetOrdenation[i].setSize(sizeVector);
            vetOrdenation[i].setOrdem(static_cast<int> (order));
            DAOOrdenation::insert(vetOrdenation[i]);
        }
    } else ShowError::error("Os dados não serão salvos pois o banco não foi carregado corretamente.");

    setStatus(50, "Limpando os vetores...");
    for(int i = 0; i <= countAlgo; i++)
    {
        delete vectors[i];
        vectors[i] = nullptr;
    }

    setStatus(-1, "Pronto...");
}

void Ordenation::setGridTimes()
{
    setStatus(-1, "Preenchendo grid de tempos...");
    ui->tableWidgetAlgoXTemp->clear();
    ui->tableWidgetAlgoXTemp->setColumnCount(2);
    ui->tableWidgetAlgoXTemp->setHorizontalHeaderItem(0, new QTableWidgetItem("Algoritimo"));
    ui->tableWidgetAlgoXTemp->setHorizontalHeaderItem(1, new QTableWidgetItem("Tempo de execução"));
    ui->tableWidgetAlgoXTemp->setColumnWidth(1, 160);

    foreach (QString item, listAlgoritmosSelected) {
        int i = mapAlgo.key(item);
        ui->tableWidgetAlgoXTemp->insertRow(ui->tableWidgetAlgoXTemp->rowCount());
        ui->tableWidgetAlgoXTemp->setItem(ui->tableWidgetAlgoXTemp->rowCount() - 1, 0,
                                          new QTableWidgetItem(vetOrdenation[i].getAlgorithm()));
        ui->tableWidgetAlgoXTemp->setItem(ui->tableWidgetAlgoXTemp->rowCount() - 1, 1,
                                          new QTableWidgetItem(QString::number(vetOrdenation[i].getTime())));
    }
    setStatus(-1, "Pronto...");
}

void Ordenation::resetTable()
{
    //resetando o grid de tempo
    ui->tableWidgetAlgoXTemp->clear();
    ui->tableWidgetAlgoXTemp->setRowCount(0);
    ui->tableWidgetAlgoXTemp->setColumnCount(0);

    //resetando o grid dos vetores
    ui->tableWidgetVectores->clear();
    ui->tableWidgetVectores->setColumnCount(0);
    ui->tableWidgetVectores->setRowCount(0);
}
