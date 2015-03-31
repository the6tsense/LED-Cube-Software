#ifndef USBHANDLER_H
#define USBHANDLER_H

#include "rs232.h"
#include <iostream>
#include <math.h>

#include "cubeTools.h"
#include "effecthandler.h"
#include "effect.h"

class EffectHandler;

class usbHandler {
private:
    int m_port;
public:
    usbHandler();
    ~usbHandler();
    void test(bool xy);
    bool openPort(void);
    void sendUpdate(void);
};

#endif // USBHANDLER_H
