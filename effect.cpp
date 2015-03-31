#include "effect.h"

array3d Effect::s_cubearray = *(new array3d(8));
int Effect::s_cubeSize = 0;
int Effect::s_effectAmount = 0;

Effect::Effect()
{
    s_effectAmount++;
}

Effect::~Effect()
{
    s_effectAmount--;
}

int Effect::getTime(void)
{
    return m_time;
}

QString Effect::getKey(void)
{
    return m_key;
}

int Effect::getEffectAmount(void)
{
    return s_effectAmount;
}

int Effect::getCubeSize(void)
{
    return s_cubeSize;
}

void Effect::setCubeSize(int cubeSize)
{
    s_cubeSize = cubeSize;
}

/******************************** effect helper functions *****************************/

bool* Effect::mirror(int x, int y, int z, int side)
{
    switch(side)
    {
        case 0:
            return s_cubearray(x, y, z);
            break;
        case 1:
            return s_cubearray(x, y, s_cubeSize - z - 1);
            break;
        case 2:
            return s_cubearray(x, z, y);
            break;
        case 3:
            return s_cubearray(x, s_cubeSize - z - 1, y);
            break;
        case 4:
            return s_cubearray(z, x, y);
            break;
        case 5:
            return s_cubearray(s_cubeSize - z - 1, x, y);
            break;
        default:
            std::cout << "Invalid side: " << side << std::endl;
            return s_cubearray(0, 0, 0);
    }
}

void Effect::switchLayer(int z, int side, bool isOn)
{
    for(int x = 0; x < s_cubeSize; x++)
    {
        for(int y = 0; y < s_cubeSize; y++)
        {
            *mirror(x, y, z, side) = isOn;
        }
    }
}

void Effect::shiftLayer(int z, int side, bool isInvert)
{
    for(int x = 0; x < s_cubeSize; x++)
    {
        for(int y = 0; y < s_cubeSize; y++)
        {
            if(*mirror(x, y, z, side))
            {
                *mirror(x, y, z - 1, side) = !isInvert;
            }
            else
            {
                *mirror(x, y, z - 1, side) = isInvert;
            }
        }
    }
}

void Effect::clearCube(void)
{
    for(int x = 0; x < s_cubeSize; x++)
    {
        for(int y = 0; y < s_cubeSize; y++)
        {
            for(int z = 0; z < s_cubeSize; z++)
            {
                *s_cubearray(x, y, z) = false;
            }
        }
    }
}
