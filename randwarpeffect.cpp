#include "randwarpeffect.h"

RandWarpEffect::RandWarpEffect() :
    m_time(getCubeSize() * 3 * 10)
{}

void RandWarpEffect::calc(int status)
{
    static int side = 0;
    static int* pattern = (int*) malloc(pow(getCubeSize(), 2) * sizeof(int));

    if(status % (getCubeSize() * 3) == 0)
    {
        int newSide = rand() % 6;

        while(newSide == side)
        {
            newSide = rand() % 6;
        }
        side = newSide;

        for(int i = 0; i < pow(getCubeSize(), 2); i++)
        {
            pattern[i] = rand() % getCubeSize();
        }
        clearCube();
    }

    if(status % (getCubeSize() * 3) < getCubeSize())
    {
        if(status % (getCubeSize() * 3) > 0)
        {
            for(int x = 0; x < getCubeSize(); x++)
            {
                for(int y = 0; y < getCubeSize(); y++)
                {
                    if(pattern[x + y * getCubeSize()] > status % (getCubeSize() * 3) - 1)
                    {
                        *mirror(x, y, (status % (getCubeSize() * 3) - 1), side) = false;
                    }
                }
            }
        }
        //iterate through whole plane
        for(int x = 0; x < getCubeSize(); x++)
        {
            for(int y = 0; y < getCubeSize(); y++)
            {
                if(pattern[x + y * getCubeSize()] >= status % (getCubeSize() * 3))
                {
                    *mirror(x, y, status % (getCubeSize() * 3), side) = true;
                }
                //end effect
                else
                {
                    *mirror(x, y, status % (getCubeSize() * 3), side) = false;
                }
            }
        }
    }
    else if(status % (getCubeSize() * 3) > 2 * getCubeSize() - 1)
    {
        if(status % (getCubeSize() * 3) > 2 * getCubeSize())
        {
            for(int x = 0; x < getCubeSize(); x++)
            {
                for(int y = 0; y < getCubeSize(); y++)
                {
                    if(pattern[x + y * getCubeSize()]
                       <= (status % (getCubeSize() * 3) - 2 * getCubeSize() - 1))
                    {
                        *mirror(x,
                                        y,
                                        (status % (getCubeSize() * 3) - 2 * getCubeSize() - 1),
                                        side
                                        ) = false;
                    }
                }
            }
        }
        //iterate through whole plane
        for(int x = 0; x < getCubeSize(); x++)
        {
            for(int y = 0; y < getCubeSize(); y++)
            {
                if(pattern[x + y * getCubeSize()] <= (status % (getCubeSize() * 3) - 2 * getCubeSize()))
                {
                    *mirror(x, y, (status % (getCubeSize() * 3) - 2 * getCubeSize()), side) = true;
                }
                else
                {
                    *mirror(x, y, (status % (getCubeSize() * 3) - 2 * getCubeSize()), side) = false;
                }
            }
        }
    }
}
