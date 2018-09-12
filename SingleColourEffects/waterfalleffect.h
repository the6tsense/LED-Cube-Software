#ifndef WATERFALLEFFECT_H
#define WATERFALLEFFECT_H

#include "SingleColourEffect.h"

class WaterfallEffect : public SingleColourEffect
{
private:
    int m_x, m_y;

public:
    WaterfallEffect(QString name);

    void calc(int status);
};

#endif // WATERFALLEFFECT_H
