#ifndef RAINEFFECT_H
#define RAINEFFECT_H

#include "effect.h"

class RainEffect : public Effect
{
private:
    int m_time;

public:
    RainEffect();

    void calc(int status);
    int getTime(void);
};

#endif // RAINEFFECT_H
