#include "fullcoloureffect.h"

Array3d* FullColourEffect::s_cubearrayr = nullptr;
Array3d* FullColourEffect::s_cubearrayg = nullptr;
Array3d* FullColourEffect::s_cubearrayb = nullptr;
int FullColourEffect::s_cubeSize = 0;
int FullColourEffect::s_effectAmount = 0;

FullColourEffect::FullColourEffect()
{
    s_effectAmount++;
}

FullColourEffect::~FullColourEffect()
{
    s_effectAmount--;
}

Array3d& FullColourEffect::cube(COLOUR c)
{
    if(c == RED)
    {
        return *s_cubearrayr;
    }
    else if(c == GREEN)
    {
        return *s_cubearrayg;
    }
    return *s_cubearrayb;
}

int FullColourEffect::getEffectAmount(void)
{
    return s_effectAmount;
}

int FullColourEffect::getCubeSize(void)
{
    return s_cubeSize;
}

void FullColourEffect::setCubeSize(int cubeSize)
{
    s_cubeSize = cubeSize;
    if(s_cubearrayr != nullptr)
    {
        delete(s_cubearrayr);
    }

    if(s_cubearrayg != nullptr)
    {
        delete(s_cubearrayg);
    }

    if(s_cubearrayb != nullptr)
    {
        delete(s_cubearrayb);
    }

    s_cubearrayr = new Array3d(s_cubeSize);
    s_cubearrayg = new Array3d(s_cubeSize);
    s_cubearrayb = new Array3d(s_cubeSize);
}

/******************************** effect helper functions *****************************/

unsigned char& FullColourEffect::mirror(int x, int y, int z, COLOUR c, int side)
{
    switch(side)
    {
        case 0:
            return cube(c)(x, y, z);
            break;
        case 1:
            return cube(c)(x, y, s_cubeSize - z - 1);
            break;
        case 2:
            return cube(c)(x, z, y);
            break;
        case 3:
            return cube(c)(x, s_cubeSize - z - 1, y);
            break;
        case 4:
            return cube(c)(z, x, y);
            break;
        case 5:
            return cube(c)(s_cubeSize - z - 1, x, y);
            break;
        case 6:
            return cube(c)(s_cubeSize - x - 1, s_cubeSize - y - 1, z);
            break;
        case 7:
            return cube(c)(x, s_cubeSize - y - 1, s_cubeSize - z - 1);
            break;
        case 8:
            return cube(c)(s_cubeSize - x - 1, s_cubeSize - y - 1, s_cubeSize - z - 1);
            break;
        default:
            std::cout << "Invalid side: " << side << std::endl;
            return cube(c)(0, 0, 0);
    }
}

void FullColourEffect::setLayer(int z, COLOUR c, int side, unsigned char value)
{
    for(int x = 0; x < s_cubeSize; x++)
    {
        for(int y = 0; y < s_cubeSize; y++)
        {
            mirror(x, y, z, c, side) = value;
        }
    }
}

void FullColourEffect::shiftLayer(int z, int side)
{
    for(int x = 0; x < s_cubeSize; x++)
    {
        for(int y = 0; y < s_cubeSize; y++)
        {
            mirror(x, y, z - 1, RED, side) = mirror(x, y, z, RED, side);
            mirror(x, y, z - 1, GREEN, side) = mirror(x, y, z, GREEN, side);
            mirror(x, y, z - 1, BLUE, side) = mirror(x, y, z, BLUE, side);
        }
    }
}

void FullColourEffect::clearCube(void)
{
    if(s_cubearrayr != nullptr)
    {
        s_cubearrayr->clear();
    }

    if(s_cubearrayg != nullptr)
    {
        s_cubearrayg->clear();
    }

    if(s_cubearrayb != nullptr)
    {
        s_cubearrayb->clear();
    }
}
