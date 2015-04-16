#ifndef EFFECT_H
#define EFFECT_H

#include "array3d.h"
#include <QString>

class Effect
{
private:
    static int s_effectAmount;
    static int s_cubeSize;
    static Array3d* s_cubearray;

    int m_time;
    QString m_key;

public:
    Effect();
    virtual ~Effect();

    virtual void calc(int status) = 0;
    virtual void end(void);
    void setTime(int time);
    virtual int getTime(void);
    void setKey(QString key);
    QString getKey(void);

    static Array3d& cube(void);
    static int getEffectAmount(void);
    static int getCubeSize(void);
    static void setCubeSize(int cubeSize);

    /*effect helper*/
    static bool& mirror(int x, int y, int z, int side);
    static void switchLayer(int z, int side, bool isOn);
    static void shiftLayer(int z, int side, bool isInvert);
    static void clearCube(void);
};

#endif // EFFECT_H
