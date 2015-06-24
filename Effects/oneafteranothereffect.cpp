#include "oneafteranothereffect.h"

OneAfterAnotherEffect::OneAfterAnotherEffect(QString name) :
    m_x(0),
    m_y(0),
    m_z(0),
    m_on(true)
{
    setKey(name);
}

void OneAfterAnotherEffect::calc(int status)
{
    Q_UNUSED(status);

    cube()(m_x, m_y, m_z) = m_on;

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
        m_on = !m_on;
    }
}


int OneAfterAnotherEffect::getTime(void)
{
    return 2 * pow(getCubeSize(), 3);
}
