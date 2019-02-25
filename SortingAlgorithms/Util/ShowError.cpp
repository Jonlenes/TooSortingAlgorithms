#include "ShowError.h"

#include <QMessageBox>

void ShowError::error(const string &e, bool aviso)
{
    if (aviso)
        QMessageBox::information(NULL, "Aviso", QString::fromStdString(e));
    else
        QMessageBox::information(NULL, "Error", QString::fromStdString(e));;
}
