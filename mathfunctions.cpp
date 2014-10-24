#include "mathfunctions.h"

MathFunctions::MathFunctions(int cubeSize) : cubeSize(cubeSize) {}

int MathFunctions::linearWave(int x, int y, int t) {
    return floor(cubeSize * sin(M_PI / cubeSize * t + x * (M_PI / cubeSize)) + cubeSize) / 2;
}

int MathFunctions::diagonalWave(int x, int y, int t) {
    return floor((cubeSize * sin(M_PI / cubeSize * t + x * (M_PI / cubeSize) + y * (M_PI / cubeSize)) + cubeSize) / 2);
}

int MathFunctions::midWave(int x, int y, int t) {
    int dist = ceil(sqrt(pow(x - cubeSize / 2, 2) + pow(y - cubeSize / 2, 2)));
    return floor(cubeSize * sin(M_PI / cubeSize * t + dist * (M_PI / cubeSize)) + cubeSize) / 2;
}


