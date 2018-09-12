#ifndef USBHANDLER_H
#define USBHANDLER_H

#include "rs232.h"
#include <iostream>
#include <math.h>

#include "cubeTools.h"
#include "effecthandler.h"
#include "SingleColourEffects/SingleColourEffect.h"
#include "FullColourEffects/fullcoloureffect.h"

class EffectHandler;

class UsbHandler {
private:
    int m_port;

    void fullColourInnerLoop(int z, FullColourEffect::COLOUR c, unsigned char*& pstream);

public:
    UsbHandler();
    ~UsbHandler();
    void test(bool xy);
    bool openPort(void);
    void sendSingleColourUpdate(void);
    void sendFullColourUpdate(void);
};

#endif // USBHANDLER_H
