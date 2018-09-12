#ifndef FULLCOLOUREFFECT_H
#define FULLCOLOUREFFECT_H

#include "Array/array3d.h"
#include "effect.h"
#include <stdlib.h>

class FullColourEffect : public Effect
{
private:
    static int s_effectAmount;
    static int s_cubeSize;
    static Array3d* s_cubearrayr;
    static Array3d* s_cubearrayg;
    static Array3d* s_cubearrayb;

public:
    FullColourEffect();
    virtual ~FullColourEffect();

    enum COLOUR {
        RED,
        GREEN,
        BLUE
    };

    static Array3d& cube(COLOUR c);
    static int getEffectAmount(void);
    static int getCubeSize(void);
    static void setCubeSize(int cubeSize);

    /*effect helper*/
    static unsigned char& mirror(int x, int y, int z, COLOUR c, int side);
    static void setLayer(int z, COLOUR c, int side, unsigned char value);
    static void shiftLayer(int z, int side);
    static void clearCube(void);

};

#endif // FULLCOLOUREFFECT_H
