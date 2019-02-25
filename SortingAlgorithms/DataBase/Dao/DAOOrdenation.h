#ifndef DAOORDENATION_H
#define DAOORDENATION_H

#include "../Model/MOrdenation.h"
#include <list>
#include <QString>

class DAOOrdenation
{
public:
    static std::list<long long> getSizes(QString filterAlgo = "");
    static long long maxSize();
    static double maxTime();
    static std::list<MOrdenation> mediumTime(QString filterAlgo = "");
    static void insert(const MOrdenation &ordenation);
    static QStringList getAlgorithms();

    static void setFilter(int ordem, QStringList listAlg, QStringList listSize);
    static void clearFilter();

private:
    static QString filter;
};

#endif // DAOORDENATION_H
