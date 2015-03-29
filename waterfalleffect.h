#ifndef WATERFALLEFFECT_H
#define WATERFALLEFFECT_H

#include "effect.h"

class WaterfallEffect : public Effect
{
private:
    int m_time;
    int m_x, m_y;

public:
    WaterfallEffect();

    void calc(int status);
};

#endif // WATERFALLEFFECT_H
