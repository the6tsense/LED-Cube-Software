#ifndef EFFECTHANDLER_H
#define EFFECTHANDLER_H

#define M_PI 3.14159

#include "effect.h"
#include "usbhandler.h"
#include "cubeTools.h"
#include "cubewindow.h"
#include "fireworkseffect.h"
#include "mathfunctioneffect.h"
#include "oneafteranothereffect.h"
#include "plainseffect.h"
#include "raineffect.h"
#include "randwarpeffect.h"
#include "shrinkboxeffect.h"
#include "texteffect.h"
#include "waterfalleffect.h"
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <math.h>
#include <vector>

class CubeWindow;
class usbHandler;

class EffectHandler {
private:
    bool m_isActive;
    bool m_isUpdateReady;
    int m_status;
    unsigned int m_effectSpeed;
    std::vector<Effect*> m_effects;
    usbHandler* m_usb;
    QString m_currentEffect;
    vector<thread> m_threads;
    const CubeWindow* m_window;

    void effectLoop(void);
    void effect(void);
    void initEffectList(void);

public:
    EffectHandler(CubeWindow* const window);
    ~EffectHandler();

    bool start(void);
    void changeEffect(int effectNum);
    void nextEffect(void);
};

#endif // EFFECTHANDLER_H
