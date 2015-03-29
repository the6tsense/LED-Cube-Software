#ifndef SHRINKBOXEFFECT_H
#define SHRINKBOXEFFECT_H

#include "effect.h"

class ShrinkBoxEffect : public Effect
{
private:
    int m_time;
    int m_edge;

public:
    ShrinkBoxEffect();

    void calc(int status);
};

#endif // SHRINKBOXEFFECT_H
