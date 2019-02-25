#include "PopUp.h"
#include "ui_PopUp.h"

#include <string>

PopUp * PopUp::popUp = __null;

PopUp::PopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopUp)
{
    ui->setupUi(this);
    ui->listWidget->setSelectionMode(QAbstractItemView ::MultiSelection);
    setModal(true);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->pushButtonFiltrar->setFocus();
}

PopUp::~PopUp()
{
    delete ui;
}

void PopUp::on_pushButtonFiltrar_clicked()
{
    if(ui->listWidget->selectedItems().count() == 0)
    {
        strFiltro->clear();
        close();
    }
    strFiltro->clear();
    foreach (QListWidgetItem *i, ui->listWidget->selectedItems()) {
        strFiltro->append(i->text());
    };
    close();
}

QString PopUp::showPopUp(QWidget *parent, QStringList listValores, QStringList &listFiltros, QString title)
{
    popUp = new PopUp(parent);

    popUp->setWindowTitle(title);
    popUp->ui->listWidget->clear();
    popUp->strFiltro = &listFiltros;
    popUp->ui->listWidget->addItems(listValores);

    if (listFiltros.count() > 0) {
        for (int i = 0; i < popUp->ui->listWidget->count(); i++) {
            QListWidgetItem *item = popUp->ui->listWidget->item(i);
            foreach (QString filtro, listFiltros) {
                if (item->text() == filtro) {
                    item->setSelected(true);
                    break;
                }
            }
        }
    }
    popUp->exec();

    delete popUp;
    popUp = nullptr;

    if (listFiltros.count() == 0)
        return "Nenhum";
    else if (listFiltros.count() == 1)
        return listFiltros.at(0);
    else if (listFiltros.count() == listValores.count())
        return "Todos";
    else
        return "Vários";
}


void PopUp::on_pushButtonLimpar_clicked()
{
    foreach (QListWidgetItem *i, ui->listWidget->selectedItems()) {
            ui->listWidget->setItemSelected(i, false);
    };
}

void PopUp::on_pushButton_clicked()
{
    for (int i = 0; i < popUp->ui->listWidget->count(); i++) {
        popUp->ui->listWidget->item(i)->setSelected(true);
    }
}

void PopUp::on_lineEdit_textEdited(const QString &arg1)
{
    for (int i = 0; i < popUp->ui->listWidget->count(); i++) {
        QListWidgetItem *item = popUp->ui->listWidget->item(i);
        if (!item->text().toUpper().startsWith(arg1.toUpper())) item->setHidden(true);
        else item->setHidden(false);
    }
}
