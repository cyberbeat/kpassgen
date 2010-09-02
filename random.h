#ifndef RANDOM_H
#define RANDOM_H
#include <limits>
#include <time.h>

class Random
{
public:
    Random() { qseed(time(NULL)); }
    Random(int seed) { qseed(seed); }

    int getInt() { return qrand(); }
    int getInt(int max) { return qrand() % max; }
    int getInt(int min, int max) { return ((int) qrand() % max) + min; }

    unsigned int getUint() { return qrand(); }
    unsigned int getUint(int max) { return qrand() % max; }
    unsigned int getUint(int min, int max) { return (qrand() % max) + min; }
};

#endif // RANDOM_H
