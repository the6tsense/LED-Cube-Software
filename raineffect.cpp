#include "raineffect.h"

RainEffect::RainEffect() :
    m_time(200)
{}

void RainEffect::calc(int status)
{
    //only every second iteration
    if(status % 2)
    {
        //shift every layer one down
        for(int z = 1; z < getCubeSize(); z++)
        {
            shiftLayer(z, 0, false);
        }

        //switch off topmost layer
        switchLayer(getCubeSize() - 1, 0, false);

        //select a random number of voxels
        int i = rand() % (int)(pow(getCubeSize(), 2.0) / 7) + getCubeSize();

        //switch voxels at random locations on
        for(; i > 0; i--)
        {
            int x = rand() % getCubeSize();
            int y = rand() % getCubeSize();
            *s_cubearray(x, y, getCubeSize() - 1) = true;
        }
    }
}
