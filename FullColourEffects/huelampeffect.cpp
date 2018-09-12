#include "huelampeffect.h"

HueLampEffect::HueLampEffect(QString name) :
    m_red(0),
    m_green(0),
    m_blue(0)
{
    setKey(name);
}

void HueLampEffect::calc(int status)
{
    //initial condition
    if(status < COLOURMAX)
    {
        m_red++;
    }
    //full red
    else if(status < 2 * COLOURMAX)
    {
        m_green++;
    }
    //full red and green
    else if(status < 3 * COLOURMAX)
    {
        m_blue++;
    }
    else if(status < 4 * COLOURMAX)
    {
        m_red--;
    }
    else if(status < 5 * COLOURMAX)
    {
        m_green--;
    }
    else if(status < 6 * COLOURMAX)
    {
        m_red++;
    }
    else if(status < 7 * COLOURMAX)
    {
        m_blue--;
    }
    else if(status < 8 * COLOURMAX)
    {
        m_green++;
    }
    else if(status < 9 * COLOURMAX)
    {
        m_red--;
    }
    else
    {
        m_green--;
    }

    cube(RED).setAll(m_red);
    cube(GREEN).setAll(m_green);
    cube(BLUE).setAll(m_blue);
}

int HueLampEffect::getTime(void)
{
    return 10 * COLOURMAX;
}
