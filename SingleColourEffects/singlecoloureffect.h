#ifndef SINGLECOLOUREFFECT_H
#define SINGLECOLOUREFFECT_H

#include "Array/array3d.h"
#include "effect.h"
#include <QString>

class SingleColourEffect : public Effect
{
private:
    static int s_effectAmount;
    static int s_cubeSize;
    static Array3d* s_cubearray;

public:
    SingleColourEffect();
    virtual ~SingleColourEffect();

    static Array3d& cube(void);
    static int getEffectAmount(void);
    static int getCubeSize(void);
    static void setCubeSize(int cubeSize);

    /*effect helper*/
    static unsigned char& mirror(int x, int y, int z, int side);
    static void switchLayer(int z, int side, bool isOn);
    static void shiftLayer(int z, int side, bool isInvert);
    static void clearCube(void);
};

#endif // EFFECT_H
