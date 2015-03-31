#include "plainseffect.h"

PlainsEffect::PlainsEffect() :
    m_time(getCubeSize() * 6 * 4)
{}

void PlainsEffect::calc(int status)
{
    if(status == 0)
    {
        switchLayer(0, 0, true);
    }
    else
    {
        switchLayer((status - 1) % getCubeSize(),
                    floor((status - 1) % (getCubeSize() * 6) / getCubeSize()),
                    false);
        switchLayer(status % getCubeSize(),
                    floor(status % (getCubeSize() * 6) / getCubeSize()),
                    true);
    }
}
