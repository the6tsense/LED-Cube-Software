#ifndef SHRINKBOXEFFECT_H
#define SHRINKBOXEFFECT_H

#include "effect.h"

class ShrinkBoxEffect : public Effect
{
private:
    int m_side;
    int m_stat;
    bool m_even;
    bool m_isGrowing;

public:
    ShrinkBoxEffect(QString name);

    void calc(int status);
    int getTime(void);
};

#endif // SHRINKBOXEFFECT_H
