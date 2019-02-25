#ifndef CONNECTIONDB_H
#define CONNECTIONDB_H

#include <QtSql>
class QWidget;

class ConnectionDb
{
public:
    static void open(QString pathDataBase, QString type);
    static QSqlQuery query(const QString &strQuery);
    static void execute(const QString &strQuery);
    static void close();
    static void open();
    static bool isConnected();

private:
    static QSqlDatabase *db;
    static bool connected;
};

#endif // CONNECTIONDB_H
