#ifndef ONEAFTERANOTHEREFFECT_H
#define ONEAFTERANOTHEREFFECT_H

#include "effect.h"
#include <math.h>

class OneAfterAnotherEffect : public Effect
{
private:
    int m_x, m_y, m_z;
    bool m_on;

public:
    OneAfterAnotherEffect(QString name);

    void calc(int status);
    int getTime(void);
};

#endif // ONEAFTERANOTHEREFFECT_H
