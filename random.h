#ifndef RANDOM_H
#define RANDOM_H
#include <limits>
#include <time.h>
#include <QtGlobal>

class Random
{
public:
    static void init()         { qsrand(time(NULL)); }
    static void init(int seed) { qsrand(seed); }

    static int nextInt() { return qrand(); }
    static int nextInt(int max) { return qrand() % max; }
    static int nextInt(int min, int max) { return ((int) qrand() % max) + min; }

    static unsigned int nextUint() { return qrand(); }
    static unsigned int nextUint(int max) { return qrand() % max; }
    static unsigned int nextUint(int min, int max) { return (qrand() % max) + min; }

private:
    Random() {}
};

#endif // RANDOM_H
