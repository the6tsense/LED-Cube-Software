#ifndef USBHANDLER_H
#define USBHANDLER_H

#include <iostream>
#include <math.h>
#include "rs232.h"
#include "constants.h"

#include "cubeTools.h"
#include "effecthandler.h"

class EffectHandler;

class usbHandler {
private:
    int port;

public:
    usbHandler(int comPort);
    ~usbHandler();
    void test(bool xy);
    bool openPort(void);
    void sendUpdate(int cubeSize, array3d* const array);
};

#endif // USBHANDLER_H
