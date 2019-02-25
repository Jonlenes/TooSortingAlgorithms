#include "generatevector.h"

#include <cstdlib>
#include <string>

void GenerateVector::crescent(long long *&vector, long long valueBegin, int n)
{
    vector = new long long[n];
    for (long long i = 0; i < n; i++) {
        vector[i] = valueBegin;
        valueBegin++;
    }
}
void GenerateVector::decrescent(long long *&vector, long long valueBegin, int n)
{
    vector = new long long[n];
    for (long long i = 0; i < n; i++) {
        vector[i] = valueBegin;
        valueBegin--;
    }
}

void GenerateVector::random(long long *&vector, int n)
{
    vector = new long long[n];
    for (long long i = 0; i < n; i++) {
        vector[i] = rand();
    }
}

void GenerateVector::all(long long *&vector, int n, Order order, long long valueBegin)
{
    try {
        if (vector) delete vector;

        switch (order) {
        case Order::Crescent:
            crescent(vector, valueBegin, n);
            break;
        case Order::Decrescent:
            decrescent(vector, valueBegin, n);
            break;
        case Order::Random:
            random(vector, n);
            break;
        default:
            break;
        }
    }
    catch (std::bad_alloc& ba) {
        throw std::string("Memória insuficiente.");
    }
    catch (...) {
        throw std::string("Erro desconhecido.");
    }
}
