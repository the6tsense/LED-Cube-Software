#include "oneafteranothereffect.h"

OneAfterAnotherEffect::OneAfterAnotherEffect() :
    m_time(2 * pow(getCubeSize(), 3)),
    m_x(0),
    m_y(0),
    m_z(0)
{}

void OneAfterAnotherEffect::calc(int status)
{
    *s_cubearray(m_x, m_y, m_z) = true;

    m_x++;

    if(m_x >= getCubeSize()) {
        m_x = 0;
        m_y++;
    }

    if(m_y >= getCubeSize()) {
        m_y = 0;
        m_z++;
    }

    if(m_z >= getCubeSize()) {
        m_x = 0;
        m_y = 0;
        m_z = 0;
    }
}
