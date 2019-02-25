#ifndef POPUP_H
#define POPUP_H

//includes Qt
#include <QDialog>

namespace Ui {
class PopUp;
}

class PopUp : public QDialog
{
    Q_OBJECT

public:
    ~PopUp();
     static QString showPopUp(QWidget *parent, QStringList strValues, QStringList &strFiltro, QString title = "PopUp");

private slots:
    void on_pushButtonFiltrar_clicked();

    void on_pushButtonLimpar_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

private:
    explicit PopUp(QWidget *parent = 0);

    Ui::PopUp *ui;
    QStringList *strFiltro;
    static PopUp *popUp;
};
#endif // POPUP_H
