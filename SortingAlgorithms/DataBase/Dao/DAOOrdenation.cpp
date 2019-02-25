//includes proprios
#include "DAOOrdenation.h"
#include "../Connection/ConnectionDb.h"
#include "Enums.h"
#include "Exceptions/Exception.h"
#include "Util/ShowError.h"

//include Qt
#include <QSqlQuery>

using namespace std;

QString DAOOrdenation::filter = "";

void DAOOrdenation::setFilter(int ordem, QStringList listAlg, QStringList listSize)
{
    //filtrando a ordem
    filter = " WHERE Ordenation.OrderOrd = " + QString::number(ordem) + "      ";

    //filtrando os algoritmos
    if (!listAlg.isEmpty()) {
        filter += " AND Ordenation.Algo IN (";
        foreach (QString item , listAlg) {
            filter += "'" + item + "'";
            if (item != listAlg.at(listAlg.count() - 1)) filter += ",";
        }
        filter += ")    ";
    }

    //filtrando os tamanhos
    if (!listSize.isEmpty()) {
        filter += " AND Ordenation.Size_Vector IN (";
        foreach (QString item , listSize) {
            filter += item;
            if (item != listSize.at(listSize.count() - 1)) filter += ",";
        }
        filter += ")     ";
    }
}

void DAOOrdenation::clearFilter()
{
    filter.clear();
}

list<long long> DAOOrdenation::getSizes(QString filterAlgo)
{
    QSqlQuery record;
    QString sql;
    list<long long> listSize;

    sql = sql + "SELECT Size_Vector FROM Ordenation "
            + filter;
    if (!filterAlgo.isEmpty())
        sql += " AND Ordenation.Algo = '" + filterAlgo + "'   ";
    sql = sql + " GROUP BY(Size_Vector) ORDER BY (Size_Vector)";

    try {

        record = ConnectionDb::query(sql);
        while (record.next()) {
            listSize.push_back(record.value(0).toLongLong());
        }

    } catch (const Exception &e) {
        ShowError::error(e.what());
    }

    return listSize;
}

long long DAOOrdenation::maxSize()
{
    try {

        QSqlQuery record =  ConnectionDb::query("SELECT MAX(Size_Vector) AS MaxSize FROM Ordenation " + filter);
        if (record.next()) return record.value(0).toLongLong();

    } catch (const Exception &e) {
        ShowError::error(e.what());
    }
    return 0;
}

double DAOOrdenation::maxTime()
{
    try {

        QSqlQuery record =  ConnectionDb::query("SELECT MAX(Times) AS MaxTime FROM Ordenation " + filter);
        if (record.next()) return record.value(0).toDouble();

    } catch (const Exception &e) {

    }
    return 0;
}

list<MOrdenation> DAOOrdenation::mediumTime(QString filterAlgo)
{
    QString sql;
    list<MOrdenation> listaOrder;

    sql =       "SELECT Ordenation.Algo, ";
    sql = sql + "       Ordenation.Size_Vector, "
            + "       (SUM(Times) / NewOrde.Freq)  AS TimeMedium, "
            + "       NewOrde.Freq "
            + "FROM   Ordenation "
            + "       INNER JOIN ( "
            + "                SELECT Algo, "
            + "                       Size_Vector, "
            + "                       COUNT(*) AS Freq "
            + "                FROM   Ordenation "
            + "                GROUP BY "
            + "                       Algo, "
            + "                       Size_Vector "
            + "            )                           AS NewOrde "
            + "            ON  Ordenation.Algo = NewOrde.Algo "
            + "            AND Ordenation.Size_Vector = NewOrde.Size_Vector "
            + filter;
    if (!filterAlgo.isEmpty())
        sql += " AND Ordenation.Algo = '" + filterAlgo + "'   ";
    sql = sql + "GROUP BY "
            + "       Ordenation.Algo, "
            + "       Ordenation.Size_Vector "
            + "ORDER BY "
            + "       Ordenation.Algo, "
            + "       Ordenation.Size_Vector";

    try {

        QSqlQuery record = ConnectionDb::query(sql);
        while (record.next()) {
            MOrdenation model = MOrdenation(record.value(ColumnTable::Algo).toString(),
                                            record.value(ColumnTable::SizeVector).toInt(),
                                            record.value(ColumnTable::TimeMedium).toDouble(),
                                            Order::Crescent);
            model.setFrequency(record.value(ColumnTable::Freq).toInt());
            listaOrder.push_back(model);
        }

    } catch (const Exception &e) {
        ShowError::error(e.what());
    }

    return listaOrder;
}

void DAOOrdenation::insert(const MOrdenation &ordenation)
{
    QSqlQuery record;
    QString sql;
    int codigo;

    sql = "SELECT COALESCE(MAX(Cod), -1) As CodMax FROM Ordenation";

    try {

        record = ConnectionDb::query(sql);
        record.next();
        codigo = record.value(0).toString().toInt() + 1;

        sql = "INSERT INTO Ordenation VALUES ("
                + QString::number(codigo) + ",'"
                + ordenation.getAlgorithm() + "',"
                + QString::number(ordenation.getSize()) + ","
                + QString::number(ordenation.getTime()) + ","
                + "NULL" + ","
                + "NULL" + ","
                + QString::number(ordenation.getOrdem()) + ")";

        ConnectionDb::execute(sql);

    } catch (const Exception &e) {
        ShowError::error(e.what());
    }
}

QStringList DAOOrdenation::getAlgorithms()
{
    QSqlQuery record;
    QString sql;
    QStringList listAlg;

    sql = "SELECT Algo FROM Ordenation   ";
    sql += "GROUP BY Algo ";

    try {

        record = ConnectionDb::query(sql);
        while (record.next()) {
            listAlg.append(record.value(0).toString());
        }

    } catch (const Exception &e) {
        ShowError::error(e.what());
    }
    return listAlg;
}
