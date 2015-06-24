#include "gameoflifeeffect.h"

GameOfLifeEffect::GameOfLifeEffect(QString name)
{
    setKey(name);
}

void GameOfLifeEffect::calc(int status)
{
    Array3d buffer = Array3d(cube());

    //Array3d buffer;
    int count = 0;

    if(status == 0)
    {
        clearCube();
        for(int i = 0; i < 0.1 * pow(getCubeSize(), 3); i++)
        {
            int x = rand() % getCubeSize();
            int y = rand() % getCubeSize();
            int z = rand() % getCubeSize();

            cube()(x, y, z) = true;
        }
    }
    else
    {
        buffer = Array3d(cube());

        for(int x = 0; x < getCubeSize(); x++)
        {
            for(int y = 0; y < getCubeSize(); y++)
            {
                for(int z = 0; z < getCubeSize(); z++)
                {
                    //born at: 4,5,6,7,8,9 stays alive at: 8,9,10
                    if(x - 1 >= 0)
                    {

                    }

                    if(x + 1 < getCubeSize())
                    {

                    }
                }
            }
        }
    }
}
