#ifndef RAINEFFECT_H
#define RAINEFFECT_H

#include "effect.h"

class RainEffect : public Effect
{
public:
    RainEffect(QString name);

    void calc(int status);
};

#endif // RAINEFFECT_H
