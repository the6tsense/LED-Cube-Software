#include "gameoflifeeffect.h"

GameOfLifeEffect::GameOfLifeEffect(QString name)
{
    setKey(name);
    setTime(300);
}

void GameOfLifeEffect::calc(int status)
{
    if(status == 0)
    {
        clearCube();
        for(int i = 0; i < 0.2 * pow(getCubeSize(), 3); i++)
        {
            int x = rand() % getCubeSize();
            int y = rand() % getCubeSize();
            int z = rand() % getCubeSize();

            cube()(x, y, z) = true;
        }
        /*cube()(0,0,0) = true;
        cube()(0,0,1) = true;
        cube()(0,1,0) = true;
        cube()(0,1,1) = true;
        cube()(1,0,0) = true;
        cube()(1,0,1) = true;
        cube()(1,1,0) = true;
        cube()(1,1,1) = true;*/
    }
    else
    {
        Array3d buffer(cube());
        bool isStillAlive = false;

        for(int x = 0; x < getCubeSize(); x++)
        {
            for(int y = 0; y < getCubeSize(); y++)
            {
                for(int z = 0; z < getCubeSize(); z++)
                {
                    int lifeNeighbors = countLivingNeighbors(buffer, x, y, z);
                    /*if(x == 0)
                    {
                        std::cout << "Debug game of Life: y: "  << y << " z: "
                                  << z << " " << lifeNeighbors << std::endl;

                    }*/

                    if(cube()(x, y, z))
                    {
                        isStillAlive = true;
                        if(lifeNeighbors < 4 || lifeNeighbors > 6)
                        {
                            //cell dies
                            cube()(x, y, z) = false;
                        }
                    }
                    else
                    {
                        if(lifeNeighbors == 5)
                        {
                            //a cell is born
                            cube()(x, y, z) = true;
                        }
                    }
                }
            }
        }

        //if every cell is already dead, start next animation
        if(!isStillAlive)
        {
            setTime(0);
        }
    }
}

int GameOfLifeEffect::countLivingNeighbors(Array3d& buf, int x, int y, int z)
{
    int lifeNeighbors = 0;
    int xPlus = x + 1;
    int xMin = x - 1;
    int yPlus = y + 1;
    int yMin = y - 1;
    int zPlus = z + 1;
    int zMin = z - 1;

    if(xMin < 0)
    {
        xMin = getCubeSize() - 1;
    }
    else if(xPlus >= getCubeSize())
    {
        xPlus = 0;
    }

    if(yMin < 0)
    {
        yMin = getCubeSize() - 1;
    }
    else if(yPlus >= getCubeSize())
    {
        yPlus = 0;
    }

    if(zMin < 0)
    {
        zMin = getCubeSize() - 1;
    }
    else if(zPlus >= getCubeSize())
    {
        zPlus = 0;
    }

    if(buf(x, y, zPlus))
    {
        lifeNeighbors++;
    }
    if(buf(x, y, zMin))
    {
        lifeNeighbors++;
    }
    if(buf(x, yPlus, z))
    {
        lifeNeighbors++;
    }
    if(buf(x, yPlus, zPlus))
    {
        lifeNeighbors++;
    }
    if(buf(x, yPlus, zMin))
    {
        lifeNeighbors++;
    }
    if(buf(x, yMin, z))
    {
        lifeNeighbors++;
    }
    if(buf(x, yMin, zPlus))
    {
        lifeNeighbors++;
    }
    if(buf(x, yMin, zMin))
    {
        lifeNeighbors++;
    }

    if(buf(xPlus, y, z))
    {
        lifeNeighbors++;
    }
    if(buf(xPlus, y, zPlus))
    {
        lifeNeighbors++;
    }
    if(buf(xPlus, y, zMin))
    {
        lifeNeighbors++;
    }
    if(buf(xPlus, yPlus, z))
    {
        lifeNeighbors++;
    }
    if(buf(xPlus, yPlus, zPlus))
    {
        lifeNeighbors++;
    }
    if(buf(xPlus, yPlus, zMin))
    {
        lifeNeighbors++;
    }
    if(buf(xPlus, yMin, z))
    {
        lifeNeighbors++;
    }
    if(buf(xPlus, yMin, zPlus))
    {
        lifeNeighbors++;
    }
    if(buf(xPlus, yMin, zMin))
    {
        lifeNeighbors++;
    }

    if(buf(xMin, y, z))
    {
        lifeNeighbors++;
    }
    if(buf(xMin, y, zPlus))
    {
        lifeNeighbors++;
    }
    if(buf(xMin, y, zMin))
    {
        lifeNeighbors++;
    }
    if(buf(xMin, yPlus, z))
    {
        lifeNeighbors++;
    }
    if(buf(xMin, yPlus, zPlus))
    {
        lifeNeighbors++;
    }
    if(buf(xMin, yPlus, zMin))
    {
        lifeNeighbors++;
    }
    if(buf(xMin, yMin, z))
    {
        lifeNeighbors++;
    }
    if(buf(xMin, yMin, zPlus))
    {
        lifeNeighbors++;
    }
    if(buf(xMin, yMin, zMin))
    {
        lifeNeighbors++;
    }

    return lifeNeighbors;
}
