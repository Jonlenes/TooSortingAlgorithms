#ifndef WEB_H
#define WEB_H

//includes proprios
#include "Enums.h"
#include "DataBase/Model/MOrdenation.h"

//includes Qt
#include <QString>
#include <QMap>

//includes c++
#include <list>

class Web
{
public:

    static void generetareHtml(const QMap<int, QString> &mapAlgo);

    static void mountHeader();
    static void mountTableMedium(const int &order, QStringList &listAlgo,
                                 QStringList &listSize, std::list<MOrdenation> listOrdenation,
                                 const QMap<int, QString> &mapAlgo);
    static void mountFooter();


    static void saveHtml(QString html);

private:
    static QString html;
    static QString *strOrder;
};

#endif // WEB_H
