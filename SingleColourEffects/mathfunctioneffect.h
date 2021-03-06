#ifndef MATHFUNCTIONEFFECT_H
#define MATHFUNCTIONEFFECT_H

#include "SingleColourEffect.h"
#include "mathfunctions.h"

class MathFunctionEffect : public SingleColourEffect
{
private:
    static MathFunctions* s_mathFunc;

    int (MathFunctions::*m_func)(int, int, int);

public:
    MathFunctionEffect(int endtime, QString name, int (MathFunctions::*function)(int, int, int));

    void calc(int status);
};

#endif // MATHFUNCTIONEFFECT_H
