#include "SingleColourEffect.h"

Array3d* SingleColourEffect::s_cubearray = nullptr;
int SingleColourEffect::s_cubeSize = 0;
int SingleColourEffect::s_effectAmount = 0;

SingleColourEffect::SingleColourEffect()
{
    s_effectAmount++;
}

SingleColourEffect::~SingleColourEffect()
{
    s_effectAmount--;
}

Array3d& SingleColourEffect::cube(void)
{
    return *s_cubearray;
}

int SingleColourEffect::getEffectAmount(void)
{
    return s_effectAmount;
}

int SingleColourEffect::getCubeSize(void)
{
    return s_cubeSize;
}

void SingleColourEffect::setCubeSize(int cubeSize)
{
    s_cubeSize = cubeSize;
    if(s_cubearray != nullptr)
    {
        delete(s_cubearray);
    }
    s_cubearray = new Array3d(s_cubeSize);
}

/******************************** effect helper functions *****************************/

unsigned char& SingleColourEffect::mirror(int x, int y, int z, int side)
{
    switch(side)
    {
        case 0:
            return cube()(x, y, z);
            break;
        case 1:
            return cube()(x, y, s_cubeSize - z - 1);
            break;
        case 2:
            return cube()(x, z, y);
            break;
        case 3:
            return cube()(x, s_cubeSize - z - 1, y);
            break;
        case 4:
            return cube()(z, x, y);
            break;
        case 5:
            return cube()(s_cubeSize - z - 1, x, y);
            break;
        case 6:
            return cube()(s_cubeSize - x - 1, s_cubeSize - y - 1, z);
            break;
        case 7:
            return cube()(x, s_cubeSize - y - 1, s_cubeSize - z - 1);
            break;
        case 8:
            return cube()(s_cubeSize - x - 1, s_cubeSize - y - 1, s_cubeSize - z - 1);
            break;
        default:
            std::cout << "Invalid side: " << side << std::endl;
            return cube()(0, 0, 0);
    }
}

void SingleColourEffect::switchLayer(int z, int side, bool isOn)
{
    for(int x = 0; x < s_cubeSize; x++)
    {
        for(int y = 0; y < s_cubeSize; y++)
        {
            mirror(x, y, z, side) = isOn;
        }
    }
}

void SingleColourEffect::shiftLayer(int z, int side, bool isInvert)
{
    for(int x = 0; x < s_cubeSize; x++)
    {
        for(int y = 0; y < s_cubeSize; y++)
        {
            if(mirror(x, y, z, side))
            {
                mirror(x, y, z - 1, side) = !isInvert;
            }
            else
            {
                mirror(x, y, z - 1, side) = isInvert;
            }
        }
    }
}

void SingleColourEffect::clearCube(void)
{
    if(s_cubearray != nullptr)
    {
        s_cubearray->clear();
    }
}
