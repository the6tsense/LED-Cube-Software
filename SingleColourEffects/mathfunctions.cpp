#include "mathfunctions.h"

MathFunctions::MathFunctions() {}

int MathFunctions::linearWave(int x, int y, int t)
{
    Q_UNUSED(y)

    return floor(SingleColourEffect::getCubeSize() *
                 sin(M_PI / SingleColourEffect::getCubeSize() * t +
                     x * (M_PI / SingleColourEffect::getCubeSize())) + SingleColourEffect::getCubeSize()) / 2;
}

int MathFunctions::diagonalWave(int x, int y, int t)
{
    return floor((SingleColourEffect::getCubeSize() *
                  sin(M_PI / SingleColourEffect::getCubeSize() * t +
                      x * (M_PI / SingleColourEffect::getCubeSize()) +
                      y * (M_PI / SingleColourEffect::getCubeSize())) +
                  SingleColourEffect::getCubeSize()) / 2);
}

int MathFunctions::midWave(int x, int y, int t)
{
    int dist = ceil(sqrt(pow(x - SingleColourEffect::getCubeSize() / 2, 2) +
                         pow(y - SingleColourEffect::getCubeSize() / 2, 2)));
    return floor(SingleColourEffect::getCubeSize() *
                 sin(M_PI / SingleColourEffect::getCubeSize() * t +
                     dist * (M_PI / SingleColourEffect::getCubeSize())) + SingleColourEffect::getCubeSize()) / 2;
}


