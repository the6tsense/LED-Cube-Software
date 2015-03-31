#include "mathfunctioneffect.h"

MathFunctions* MathFunctionEffect::s_mathFunc = new MathFunctions(getCubeSize());

MathFunctionEffect::MathFunctionEffect(int endtime,
                                       QString name,
                                       int (MathFunctions::*function)(int, int, int)
                                       ) :
    m_func(function),
    m_time(endtime),
    m_key(name)
{}

void MathFunctionEffect::calc(int status)
{
    //clear cube at beginning of each iteration
    clearCube();

    //switch through every led in a Layer
    for(int x = 0; x < getCubeSize(); x++)
    {
        for(int y = 0; y < getCubeSize(); y++)
        {
            //calculate x based on function thrown in
            int z = (s_mathFunc->*m_func)(x, y, status);
            *s_cubearray(x, y, z) = true;
        }
    }
}
