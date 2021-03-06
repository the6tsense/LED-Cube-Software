#ifndef SHRINKBOXEFFECT_H
#define SHRINKBOXEFFECT_H

#include "SingleColourEffect.h"

class ShrinkBoxEffect : public SingleColourEffect
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
