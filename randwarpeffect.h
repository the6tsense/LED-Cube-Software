#ifndef RANDWARPEFFECT_H
#define RANDWARPEFFECT_H

#include "effect.h"
#include "array2d.h"

class RandWarpEffect : public Effect
{
private:
    int m_side;
    Array2d* m_pattern;

public:
    RandWarpEffect(QString name);

    void calc(int status);
    int getTime(void);
    void end(void);
};

#endif // RANDWARPEFFECT_H
