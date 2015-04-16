#include "gameoflifeeffect.h"

GameOfLifeEffect::GameOfLifeEffect(QString name)
{
    setKey(name);
}

void GameOfLifeEffect::calc(int status)
{
    if(status == 0)
    {
        clearCube();
        for(int i = 0; i < 0.1 * pow(getCubeSize(), 3); i++)
        {
            x = rand() % getCubeSize();
            y = rand() % getCubeSize();
            z = rand() % getCubeSize();

            cube()(x, y, z) = true;
        }
    }
}
