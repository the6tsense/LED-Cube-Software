#ifndef EFFECTHANDLER_H
#define EFFECTHANDLER_H

#ifndef M_PI
#define M_PI 3.14159
#endif

#include "SingleColourEffects/singlecoloureffect.h"
#include "SingleColourEffects/fireworkseffect.h"
#include "SingleColourEffects/gameoflifeeffect.h"
#include "SingleColourEffects/mathfunctioneffect.h"
#include "SingleColourEffects/oneafteranothereffect.h"
#include "SingleColourEffects/plainseffect.h"
#include "SingleColourEffects/raineffect.h"
#include "SingleColourEffects/randwarpeffect.h"
#include "SingleColourEffects/shrinkboxeffect.h"
#include "SingleColourEffects/waterfalleffect.h"
#include "FullColourEffects/fullcoloureffect.h"
#include "FullColourEffects/huelampeffect.h"
#include "usbhandler.h"
#include "cubeTools.h"
#include "cubewindow.h"
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <math.h>
#include <vector>

class CubeWindow;
class UsbHandler;

class EffectHandler {
private:
    bool m_isActive;
    bool m_isUpdateReady;
    int m_status;
    int m_cubeColour;
    int m_cubeSize;
    unsigned int m_effectSpeed;
    std::vector<Effect*> m_effects;
    UsbHandler* m_usb;
    Effect* m_currentEffect;
    vector<thread> m_threads;
    const CubeWindow* m_window;

    void (*m_clearCube)(void);

    void effectLoop(void);
    void triggerUpdate(void);

public:
    EffectHandler(int cubeColour, int cubeSize);
    ~EffectHandler();

    bool start(void);
    void stop(void);
    void fullColourList(void);
    void singleColourList(void);
    void changeEffect(int effectNum);
    void nextEffect(void);
    void addEffect(Effect* effect);
    vector<QString> getEffects(void);
};

#endif // EFFECTHANDLER_H
