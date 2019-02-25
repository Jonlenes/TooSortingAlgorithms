#ifndef GENERATEVECTOR_H
#define GENERATEVECTOR_H

//includes proprios
#include "Enums.h"

class GenerateVector
{
public:
    static void crescent(long long  * &vector, long long  valueBegin, int n);
    static void decrescent(long long  * &vector, long long  valueBegin, int n);
    static void random(long long  * &vector, int n);
    static void all(long long  * &vector, int n, Order order, long long valueBegin = 0);
};

#endif // GENERATEVECTOR_H
