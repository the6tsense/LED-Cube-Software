#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#ifndef M_PI
#define M_PI 3.14159
#endif

#include "SingleColourEffect.h"
#include <string>
#include <math.h>

class MathFunctions
{
public:
    MathFunctions();

    int linearWave(int x, int y, int t);
    int diagonalWave(int x, int y, int t);
    int midWave(int x, int y, int t);
};

#endif // MATHFUNCTIONS_H
