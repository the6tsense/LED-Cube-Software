#ifndef PLAINSEFFECT_H
#define PLAINSEFFECT_H

#include "effect.h"

class PlainsEffect : public Effect
{
public:
    PlainsEffect(QString name);

    void calc(int status);
    int getTime(void);
};

#endif // PLAINSEFFECT_H
