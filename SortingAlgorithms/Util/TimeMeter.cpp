#include "TimeMeter.h"

timeval TimeMeter::timeBegin = timeval();
timeval TimeMeter::timeEnd = timeval();

void TimeMeter::begin()
{
    gettimeofday(&timeBegin, NULL);
}
void TimeMeter::end()
{
    gettimeofday(&timeEnd, NULL);
}
double TimeMeter::diffTime()
{
    double tf = (double)timeEnd.tv_usec + ((double)timeEnd.tv_sec * (1000000.0));
    double ti = (double)timeBegin.tv_usec + ((double)timeBegin.tv_sec * (1000000.0));
    return ((tf - ti) / 1000);
}
