#ifndef PAINTGRAPHIC_H
#define PAINTGRAPHIC_H

//includes Qt
#include <QDialog>

//include proprios
#include "WidPaintGraphic.h"

namespace Ui {
class PaintGraphic;
}

class PaintGraphic : public QDialog
{
    Q_OBJECT

public:
    explicit PaintGraphic(QWidget *parent = 0);
    ~PaintGraphic();

    static void showForm(QWidget *parent);
    void closeEvent(QCloseEvent *) override final;

    void initGUI();
    void fillComboAlgo();
    void preencheWidgetTable(QString strAlgo);

    void initFilter();
    void applyFilter();

private slots:
    void on_comboBoxOrder_activated(int index);

    void on_pushButtonFilterAlgo_clicked();

    void on_pushButtonFiltrarSize_clicked();

    void on_comboBoxAlgoritmoTabela_activated(const QString &arg1);

    void on_pushButtonGeraViewWeb_clicked();

private:
    Ui::PaintGraphic *ui;
    static PaintGraphic *frm;

    WidPaintGraphic *widgetGraphic;

    QStringList listAlgo;
    QStringList listSize;
    QStringList listFilterAlgo;
    QStringList listFilterSize;
    int ordem;
};

#endif // PAINTGRAPHIC_H
