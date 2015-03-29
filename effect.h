#ifndef EFFECT_H
#define EFFECT_H

#include "array3d.h"
#include <QString>

class Effect
{
private:
    static int s_effectAmount;
    static int s_cubeSize;

    int m_time;
    QString m_key;

public:
    static array3d s_cubearray;

    Effect();
    virtual ~Effect();

    virtual void calc(int status) = 0;
    int getTime(void);
    QString getKey(void);

    static int getEffectAmount(void);
    static int getCubeSize(void);
    static void setCubeSize(int cubeSize);

    /*effect helper*/
    static bool* mirror(int x, int y, int z, int side);
    static void switchLayer(int z, int side, bool isOn);
    static void shiftLayer(int z, int side, bool isInvert);
    static void clearCube(void);
};

#endif // EFFECT_H
