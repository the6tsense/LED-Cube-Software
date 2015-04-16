#include "randwarpeffect.h"

RandWarpEffect::RandWarpEffect(QString name) :
    m_side(0),
    m_pattern(nullptr)
{
    setKey(name);
}

int RandWarpEffect::getTime(void)
{
    return getCubeSize() * 3 * 10;
}

void RandWarpEffect::end(void)
{
    delete(m_pattern);
}

void RandWarpEffect::calc(int status)
{
    if(m_pattern == nullptr)
    {
        m_pattern = new Array2d(getCubeSize(), getCubeSize());
    }

    if(status % (getCubeSize() * 3) == 0)
    {
        int newSide = rand() % 6;

        while(newSide == m_side)
        {
            newSide = rand() % 6;
        }
        m_side = newSide;

        for(int x = 0; x < getCubeSize(); x++)
        {
            for(int y = 0; y < getCubeSize(); y++)
            {
                m_pattern->operator()(x, y) = (char) (rand() % getCubeSize());
            }
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
                    if((int)m_pattern->operator()(x, y) > status % (getCubeSize() * 3) - 1)
                    {
                        mirror(x, y, (status % (getCubeSize() * 3) - 1), m_side) = false;
                    }
                }
            }
        }
        //iterate through whole plane
        for(int x = 0; x < getCubeSize(); x++)
        {
            for(int y = 0; y < getCubeSize(); y++)
            {
                if((int)m_pattern->operator()(x, y) >= status % (getCubeSize() * 3))
                {
                    mirror(x, y, status % (getCubeSize() * 3), m_side) = true;
                }
                //end effect
                else
                {
                    mirror(x, y, status % (getCubeSize() * 3), m_side) = false;
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
                    if((int)m_pattern->operator()(x, y)
                       <= (status % (getCubeSize() * 3) - 2 * getCubeSize() - 1))
                    {
                        mirror(x,
                               y,
                               (status % (getCubeSize() * 3) - 2 * getCubeSize() - 1),
                               m_side) = false;
                    }
                }
            }
        }
        //iterate through whole plane
        for(int x = 0; x < getCubeSize(); x++)
        {
            for(int y = 0; y < getCubeSize(); y++)
            {
                if((int)m_pattern->operator()(x, y) <= (status % (getCubeSize() * 3) - 2 * getCubeSize()))
                {
                    mirror(x, y, (status % (getCubeSize() * 3) - 2 * getCubeSize()), m_side) = true;
                }
                else
                {
                    mirror(x, y, (status % (getCubeSize() * 3) - 2 * getCubeSize()), m_side) = false;
                }
            }
        }
    }
}
