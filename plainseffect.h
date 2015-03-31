#ifndef PLAINSEFFECT_H
#define PLAINSEFFECT_H

#include "effect.h"

class PlainsEffect : public Effect
{
private:
    int m_time;

public:
    PlainsEffect();

    void calc(int status);
    int getTime(void);
};

#endif // PLAINSEFFECT_H
