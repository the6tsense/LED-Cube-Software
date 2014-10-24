#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#define M_PI 3.14159

#include <string>
#include <math.h>

class MathFunctions {
private:
    int cubeSize;

public:
    MathFunctions(int cubeSize);

    int linearWave(int x, int y, int t);
    int diagonalWave(int x, int y, int t);
    int midWave(int x, int y, int t);
};

#endif // MATHFUNCTIONS_H
