#ifndef PLAINSEFFECT_H
#define PLAINSEFFECT_H

#include "SingleColourEffect.h"

class PlainsEffect : public SingleColourEffect
{
public:
    PlainsEffect(QString name);

    void calc(int status);
    int getTime(void);
};

#endif // PLAINSEFFECT_H
