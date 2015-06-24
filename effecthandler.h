#ifndef EFFECTHANDLER_H
#define EFFECTHANDLER_H

#define M_PI 3.14159

#include "Effects/effect.h"
#include "usbhandler.h"
#include "cubeTools.h"
#include "cubewindow.h"
#include "Effects/fireworkseffect.h"
#include "Effects/mathfunctioneffect.h"
#include "Effects/oneafteranothereffect.h"
#include "Effects/plainseffect.h"
#include "Effects/raineffect.h"
#include "Effects/randwarpeffect.h"
#include "Effects/shrinkboxeffect.h"
#include "Effects/texteffect.h"
#include "Effects/waterfalleffect.h"
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
    unsigned int m_effectSpeed;
    std::vector<Effect*> m_effects;
    UsbHandler* m_usb;
    Effect* m_currentEffect;
    vector<thread> m_threads;
    const CubeWindow* m_window;

    void effectLoop(void);
    void initEffectList(void);

public:
    EffectHandler(CubeWindow* const window);
    ~EffectHandler();

    bool start(void);
    void stop(void);
    void changeEffect(int effectNum);
    void nextEffect(void);
    void addEffect(Effect* effect);
    vector<QString> getEffects(void);
};

#endif // EFFECTHANDLER_H
