#ifndef USBHANDLER_H
#define USBHANDLER_H

#include "rs232.h"
#include <iostream>
#include <math.h>

#include "cubeTools.h"
#include "effecthandler.h"
#include "Effects/effect.h"

class EffectHandler;

class UsbHandler {
private:
    int m_port;
public:
    UsbHandler();
    ~UsbHandler();
    void test(bool xy);
    bool openPort(void);
    void sendUpdate(void);
};

#endif // USBHANDLER_H
