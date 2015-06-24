#ifndef CUBETOOLS_H
#define CUBETOOLS_H

#define DEBUG

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

    static double randDouble(double min, double max) {
        double f = (double)rand() / RAND_MAX;
        return min + f * (max - min);
    }
};

#endif // CUBETOOLS_H
