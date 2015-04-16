#include "effect.h"

Array3d* Effect::s_cubearray = nullptr;
int Effect::s_cubeSize = 0;
int Effect::s_effectAmount = 0;

Effect::Effect() :
    m_time(0),
    m_key("")
{
    s_effectAmount++;
}

Effect::~Effect()
{
    s_effectAmount--;
}

void Effect::end(void)
{}

void Effect::setTime(int time)
{
    m_time = time;
}

int Effect::getTime(void)
{
    return m_time;
}

void Effect::setKey(QString key)
{
    m_key = key;
}

QString Effect::getKey(void)
{
    return m_key;
}

Array3d& Effect::cube(void)
{
    return *s_cubearray;
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
    if(s_cubearray != nullptr)
    {
        delete(s_cubearray);
    }
    s_cubearray = new Array3d(s_cubeSize);
}

/******************************** effect helper functions *****************************/

bool& Effect::mirror(int x, int y, int z, int side)
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
        default:
            std::cout << "Invalid side: " << side << std::endl;
            return cube()(0, 0, 0);
    }
}

void Effect::switchLayer(int z, int side, bool isOn)
{
    for(int x = 0; x < s_cubeSize; x++)
    {
        for(int y = 0; y < s_cubeSize; y++)
        {
            mirror(x, y, z, side) = isOn;
        }
    }
}

void Effect::shiftLayer(int z, int side, bool isInvert)
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

void Effect::clearCube(void)
{
    for(int x = 0; x < s_cubeSize; x++)
    {
        for(int y = 0; y < s_cubeSize; y++)
        {
            for(int z = 0; z < s_cubeSize; z++)
            {
                cube()(x, y, z) = false;
            }
        }
    }
}
