#ifndef EFFECTHANDLER_H
#define EFFECTHANDLER_H

#define M_PI 3.14159

#include "usbhandler.h"
#include "cubeTools.h"
#include "cubewindow.h"
#include "mathfunctions.h"
#include "array3d.h"
#include "particle.h"
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <math.h>
#include <vector>

class CubeWindow;
class usbHandler;

class EffectHandler {
private:
    bool effectAlphabet[9][9][100];
    bool isActive;
    bool isUpdateReady;
    int cubeSize;
    int status;
    unsigned int effectSpeed;
    array3d cubearray;
    usbHandler* usb;
    MathFunctions* mathFunc;
    QString currentEffect;
    vector<thread> threads;
    const CubeWindow* window;

    void effectLoop();
    void initAlphabet(void);
    void effect(void);

    /*effects*/
    void waveEffect(void);
    void waveEffectXY(void);
    void plainsEffect(void);
    void rainEffect(void);
    void waterfallEffect(void);
    void oneAfterAnotherEffect(void);
    void waveEffectMid(void);
    void randWarpEffect(void);
    void fireworksEffect(void);
    void shrinkBoxEffect(void);

    /*partial effects*/
    void mathFunctionEffect(int (MathFunctions::*function)(int, int, int), int endtime);

    /*effect helper*/
    bool* mirror(int x, int y, int z, int side);
    void switchLayer(int z, int side, bool isOn);
    void shiftLayer(int z, int side, bool isInvert);

public:
    EffectHandler(int cubeSize, int comPort, CubeWindow* const window);
    ~EffectHandler();

    bool start(void);
    void changeEffect(int effectNum);
    void nextEffect(void);
};

#endif // EFFECTHANDLER_H
