#include "MOrdenation.h"

MOrdenation::MOrdenation()
{
    size = time = ordem = -1;
}

MOrdenation::MOrdenation(QString algorithm, int size, double time, Order ordem)
{
    this->algorithm = algorithm;
    this->size = size;
    this->time = time;
    this->ordem = ordem;
}

void MOrdenation::setAlgorithm(QString algorithm)
{
    this->algorithm = algorithm;
}

void MOrdenation::setSize(long long size)
{
    this->size = size;
}

void MOrdenation::setTime(double time)
{
    this->time = time;
}

void MOrdenation::setOrdem(int ordem)
{
    this->ordem = ordem;
}

void MOrdenation::setFrequency(int frequency)
{
    this->frequency = frequency;
}

QString MOrdenation::getAlgorithm() const
{
    return algorithm;
}

long long MOrdenation::getSize() const
{
    return size;
}

double MOrdenation::getTime() const
{
    return time;
}

int MOrdenation::getOrdem() const
{
    return ordem;
}

int MOrdenation::getFrequency() const
{
    return frequency;
}
