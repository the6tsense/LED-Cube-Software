#ifndef CUBETOOLS_H
#define CUBETOOLS_H

#define DEBUG

#include "array3d.h"
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

class Tools {
public:
    static void printDebug(string in) {
        #ifdef DEBUG
        cout << in << endl;
        #endif
    }

    static void clearCube(int cubeSize, array3d* cube) {
        bool* pcube = cube->operator ()(0, 0, 0);
        for(int i = 0; i < pow(cubeSize, 3.0); i++) {
            *pcube++ = false;
        }
    }

    static double randDouble(double min, double max) {
        double f = (double)rand() / RAND_MAX;
        return min + f * (max - min);
    }
};

#endif // CUBETOOLS_H
