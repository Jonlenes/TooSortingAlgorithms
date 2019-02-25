//include proprios
#include "MntDataBase.h"
#include "ui_MntDataBase.h"
#include "DataBase/Connection/ConnectionDb.h"
#include "Exceptions/Exception.h"
#include "Util/ShowError.h"

//includes Qt
#include <QKeyEvent>

MntDataBase *MntDataBase::frm = 0;

MntDataBase::MntDataBase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MntDataBase)
{
    ui->setupUi(this);
    setWindowTitle("Data Base");
}

MntDataBase::~MntDataBase()
{
    delete ui;
}

void MntDataBase::showForm(QWidget *parent)
{
    if(!frm)
        frm = new MntDataBase(parent);
    else
        frm->setParent(parent);

    if(parent) frm->setWindowFlags(parent->windowFlags());
    frm->showMaximized();
}

void MntDataBase::closeEvent(QCloseEvent *)
{
    delete frm;
    frm = nullptr;
}

void MntDataBase::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_F5)
    {
        try {

            QSqlQueryModel *model = new QSqlQueryModel();
            model->setQuery(ConnectionDb::query(ui->textEditQuery->toPlainText()));
            ui->tableViewRecord->setModel(model);

        } catch (Exception &e) {
            ShowError::error(e.getError());
        }

    }
}
