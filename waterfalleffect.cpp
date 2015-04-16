#include "waterfalleffect.h"

WaterfallEffect::WaterfallEffect(QString name)
{
    setTime(200);
    setKey(name);
}

void WaterfallEffect::calc(int status)
{
    if(status == 0)
    {
        m_x = rand() % getCubeSize();
        m_y = rand() % getCubeSize();
    }

    //shift every layer one down
    for(int z = 1; z < getCubeSize(); z++)
    {
        shiftLayer(z, 0, false);
    }

    switchLayer(getCubeSize() - 1, 0, false);

    int randNum = rand() % 3;
    m_x += randNum - 1;

    randNum = rand() % 3;
    m_y += randNum - 1;

    //keep x and y coordinates within cube
    if(m_x < 0)
    {
        m_x = 0;
    }
    else if(m_x > getCubeSize() - 1)
    {
        m_x =  getCubeSize() - 1;
    }

    if(m_y < 0)
    {
        m_y = 0;
    }
    else if(m_y > getCubeSize() - 1)
    {
        m_y = getCubeSize() - 1;
    }

    cube()(m_x, m_y, getCubeSize() - 1) = true;
    if((m_x - 1) >= 0)
    {
        cube()(m_x - 1, m_y, getCubeSize() - 1) = true;
    }

    if((m_x + 1) < getCubeSize() - 1)
    {
        cube()(m_x + 1, m_y, getCubeSize() - 1) = true;
    }

    if((m_y - 1) >= 0)
    {
        cube()(m_x, m_y - 1, getCubeSize() - 1) = true;
    }

    if((m_y + 1) < getCubeSize() - 1)
    {
        cube()(m_x, m_y + 1, getCubeSize() - 1) = true;
    }
}
