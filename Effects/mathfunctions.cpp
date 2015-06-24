#include "mathfunctions.h"

MathFunctions::MathFunctions() {}

int MathFunctions::linearWave(int x, int y, int t)
{
    Q_UNUSED(y)

    return floor(Effect::getCubeSize() *
                 sin(M_PI / Effect::getCubeSize() * t +
                     x * (M_PI / Effect::getCubeSize())) + Effect::getCubeSize()) / 2;
}

int MathFunctions::diagonalWave(int x, int y, int t)
{
    return floor((Effect::getCubeSize() *
                  sin(M_PI / Effect::getCubeSize() * t +
                      x * (M_PI / Effect::getCubeSize()) +
                      y * (M_PI / Effect::getCubeSize())) +
                  Effect::getCubeSize()) / 2);
}

int MathFunctions::midWave(int x, int y, int t)
{
    int dist = ceil(sqrt(pow(x - Effect::getCubeSize() / 2, 2) +
                         pow(y - Effect::getCubeSize() / 2, 2)));
    return floor(Effect::getCubeSize() *
                 sin(M_PI / Effect::getCubeSize() * t +
                     dist * (M_PI / Effect::getCubeSize())) + Effect::getCubeSize()) / 2;
}


