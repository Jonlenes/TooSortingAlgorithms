#include "ConnectionDb.h"
#include "Exceptions/ConnectionException.h"
#include "Exceptions/QueryException.h"

QSqlDatabase *ConnectionDb::db = 0;
bool ConnectionDb::connected = false;

void ConnectionDb::open(QString pathDataBase, QString type)
{
    connected = false;

    if (!isConnected())
        db = new QSqlDatabase();
    else
        throw ConnectionException("Data base already is connect.");

    if (!db->isOpen())
    {
        *db = QSqlDatabase::addDatabase(type);
        db->setDatabaseName(pathDataBase);

        if( !db->open() )
        {
            qDebug() << db->lastError();
            throw ConnectionException("It was not possible to connect.");
        }
    }
    connected = true;
}

QSqlQuery ConnectionDb::query(const QString &strQuery)
{
    QSqlQuery qry;
    qry.prepare(strQuery);
    if( !qry.exec() )
        throw QueryException(qry.lastError().text().toStdString());

    return qry;
}

void ConnectionDb::execute(const QString &strQuery)
{
    QSqlQuery qry;
    qry.prepare(strQuery);
    if( !qry.exec() )
        throw QueryException(qry.lastError().text().toStdString());
}

void ConnectionDb::close()
{
    db->close();
    connected = false;
}

void ConnectionDb::open()
{
    connected = db->open();
}

bool ConnectionDb::isConnected()
{
    return connected;
}

