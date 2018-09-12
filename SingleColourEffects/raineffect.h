#ifndef RAINEFFECT_H
#define RAINEFFECT_H

#include "SingleColourEffect.h"

class RainEffect : public SingleColourEffect
{
public:
    RainEffect(QString name);

    void calc(int status);
};

#endif // RAINEFFECT_H
