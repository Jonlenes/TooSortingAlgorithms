#ifndef MNTDATABASE_H
#define MNTDATABASE_H

#include <QDialog>

namespace Ui {
class MntDataBase;
}

class MntDataBase : public QDialog
{
    Q_OBJECT

public:
    explicit MntDataBase(QWidget *parent = 0);
    ~MntDataBase();

    static void showForm(QWidget *parent = 0);
    void closeEvent(QCloseEvent *) override final;
    void keyPressEvent(QKeyEvent *e) override final;

private:
    Ui::MntDataBase *ui;
    static MntDataBase *frm;
};

#endif // MNTDATABASE_H
