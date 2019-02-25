#ifndef ORDENATION_H
#define ORDENATION_H

//includes Qt
#include <QDialog>
#include <QStatusBar>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QMap>

//includes proprios
#include "Enums.h"
#include "DataBase/Model/MOrdenation.h"

namespace Ui {
class Ordenation;
}

class Ordenation : public QDialog
{
    Q_OBJECT

public:
    explicit Ordenation(QWidget *parent = 0);
    ~Ordenation();

    static void showForm(QWidget *parent = 0);
    void closeEvent(QCloseEvent *) override final;

    void initGUI();
    void initializesVectors();
    void setStatus(int porct, QString status = "-1");
    void addColumnGridVectores(IndexVector indexVector);
    void callOrdenation();
    void setGridTimes();
    void resetTable();

private slots:
    void on_pushButtonGerar_clicked();

    void on_comboBoxOrder_activated(int index);

    void on_pushButtonOrdenar_clicked();

    void on_radioButtonInCarregar_clicked();

    void on_pushButtonAlgoritmos_clicked();

private:
    Ui::Ordenation *ui;
    static Ordenation *frm;

    Order order;
    int sizeVector;
    long long **vectors;
    MOrdenation *vetOrdenation;
    QStringList listAlgoritmos;
    QStringList listAlgoritmosSelected;
    QMap<int, QString> mapAlgo;

    QStatusBar *statusBar;
    QLabel *labStatus;
    QProgressBar *prbStatus;
};

#endif // ORDENATION_H
