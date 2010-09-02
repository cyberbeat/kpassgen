#ifndef RANDOM_H
#define RANDOM_H
#include <limits>
#include <time.h>
#include <QtGlobal>

class Random
{
public:
    Random() { qsrand(time(NULL)); }
    Random(int seed) { qsrand(seed); }

    int nextInt() { return qrand(); }
    int nextInt(int max) { return qrand() % max; }
    int nextInt(int min, int max) { return ((int) qrand() % max) + min; }

    unsigned int nextUint() { return qrand(); }
    unsigned int nextUint(int max) { return qrand() % max; }
    unsigned int nextUint(int min, int max) { return (qrand() % max) + min; }
};

#endif // RANDOM_H
