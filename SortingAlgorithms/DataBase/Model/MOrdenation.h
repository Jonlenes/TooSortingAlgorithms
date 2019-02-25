#ifndef MORDENATION_H
#define MORDENATION_H

#include <QString>

#include "Enums.h"

class MOrdenation
{
public:
    MOrdenation();
    MOrdenation(QString algorithm, int size, double time, Order ordem);

    void setAlgorithm(QString algorithm);
    void setSize(long long size);
    void setTime(double time);
    void setOrdem(int ordem);
    void setFrequency(int frequency);

    QString getAlgorithm() const;
    long long getSize() const;
    double getTime() const;
    int getOrdem() const;
    int getFrequency() const;

private:
    QString algorithm;
    int size;
    double time;
    int ordem;
    int frequency;
};

#endif // MORDENATION_H
