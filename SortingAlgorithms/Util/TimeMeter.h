#ifndef TIMEMETER_H
#define TIMEMETER_H

//includes c++
#include <sys/time.h>

class TimeMeter {
public:

    static void begin();
    static void end();
    static double diffTime();

private:
    static timeval timeBegin;
    static timeval timeEnd;
};


#endif // METERTIME_H
