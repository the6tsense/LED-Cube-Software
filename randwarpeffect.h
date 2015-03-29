#ifndef RANDWARPEFFECT_H
#define RANDWARPEFFECT_H

#include "effect.h"

class RandWarpEffect : public Effect
{
private:
    int m_time;

public:
    RandWarpEffect();

    void calc(int status);
};

#endif // RANDWARPEFFECT_H
