#include "shrinkboxeffect.h"

ShrinkBoxEffect::ShrinkBoxEffect() :
    m_time(200)
{}

void ShrinkBoxEffect::calc(int status)
{
    if(status == 0)
    {
        m_edge = rand() % 8;
    }

    clearCube();

    if(status < getCubeSize())
    {
        for(int x = 0; x < getCubeSize(); x++)
        {
            for(int y = 0; y < getCubeSize(); y++)
            {
                for(int z = 0; z < getCubeSize(); z++)
                {
                    if(m_edge % 2 == 0)
                    {
                        if((x == 0 && y <= status && z <= status) ||
                           (x <= status && y == 0 && z <= status) ||
                           (x <= status && y <= status && z == 0) ||
                           (x == status && y <= status && z <= status) ||
                           (x <= status && y == status && z <= status) ||
                           (x <= status && y <= status && z == status))
                        {
                            *mirror(x, y, z, m_edge) = true;
                        }
                    }
                    else
                    {
                        if((x == getCubeSize() - 1 && y >= status && z >= status) ||
                           (x >= status && y == getCubeSize() - 1 && z >= status) ||
                           (x >= status && y >= status && z == getCubeSize() - 1) ||
                           (x == status && y >= status && z >= status) ||
                           (x >= status && y == status && z >= status) ||
                           (x >= status && y >= status && z == status))
                        {
                            *mirror(x, y, z, m_edge - 1) = true;
                        }
                    }
                }
            }
        }
    }
    else if(status > getCubeSize())
    {
        int statNew = getCubeSize() - status / 2;
        for(int x = 0; x < getCubeSize(); x++)
        {
            for(int y = 0; y < getCubeSize(); y++)
            {
                for(int z = 0; z < getCubeSize(); z++)
                {
                    if(m_edge % 2 == 0)
                    {
                        if((x == 0 && y <= statNew && z <= statNew) ||
                           (x <= statNew && y == 0 && z <= statNew) ||
                           (x <= statNew && y <= statNew && z == 0) ||
                           (x == statNew && y <= statNew && z <= statNew) ||
                           (x <= statNew && y == statNew && z <= statNew) ||
                           (x <= statNew && y <= statNew && z == statNew))
                        {
                            *mirror(x, y, z, m_edge) = true;
                        }
                    }
                    else
                    {
                        if((x == getCubeSize() - 1 && y >= statNew && z >= statNew) ||
                           (x >= statNew && y == getCubeSize() - 1 && z >= statNew) ||
                           (x >= statNew && y >= statNew && z == getCubeSize() - 1) ||
                           (x == statNew && y >= statNew && z >= statNew) ||
                           (x >= statNew && y == statNew && z >= statNew) ||
                           (x >= statNew && y >= statNew && z == statNew))
                        {
                            *mirror(x, y, z, m_edge - 1) = true;
                        }
                    }
                }
            }
        }
    }
}
