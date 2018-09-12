#ifndef RANDWARPEFFECT_H
#define RANDWARPEFFECT_H

#include "SingleColourEffect.h"
#include "Array/array2d.h"

class RandWarpEffect : public SingleColourEffect
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
