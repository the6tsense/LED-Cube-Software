#ifndef ONEAFTERANOTHEREFFECT_H
#define ONEAFTERANOTHEREFFECT_H

#include "effect.h"

class OneAfterAnotherEffect : public Effect
{
private:
    int m_time;
    int m_x, m_y, m_z;

public:
    OneAfterAnotherEffect();

    void calc(int status);
};

#endif // ONEAFTERANOTHEREFFECT_H
