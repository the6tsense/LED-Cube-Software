#include "shrinkboxeffect.h"

ShrinkBoxEffect::ShrinkBoxEffect(QString name) :
    m_stat(0)
{
    setKey(name);
}

int ShrinkBoxEffect::getTime(void)
{
    return 10 * getCubeSize();
}

void ShrinkBoxEffect::calc(int status)
{
    clearCube();

    if(status % (getCubeSize() * 2) == 0)
    {
        //0, 1, 2, 3, 5, 6, 7, 8
        int randNum = rand() % 2;
        if(randNum % 2 == 0)
        {
            m_even = true;
        }
        else
        {
            m_even = false;
        }

        m_side = randNum * 2 + 1;

        m_stat = 0;
        std::cout << randNum << std::endl;
    }

    if(status % getCubeSize() == 0)
    {
        m_isGrowing = !m_isGrowing;
    }

    for(int x = 0; x < m_stat; x++)
    {
        for(int y = 0; y < m_stat; y++)
        {
            mirror(x, y, 0, m_side) = true;
            mirror(0, x, y, m_side) = true;
            mirror(y, 0, x, m_side) = true;
            mirror(x, y, m_stat - 1, m_side) = true;
            mirror(m_stat - 1, x, y, m_side) = true;
            mirror(y, m_stat - 1, x, m_side) = true;
        }
    }

    std::cout << "m_stat: " << m_stat << std::endl;

    if(m_isGrowing)
    {
        m_stat++;
    }
    else
    {
        m_stat--;
    }
}
