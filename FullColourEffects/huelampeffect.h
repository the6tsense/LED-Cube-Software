#ifndef HUELAMPEFFECT_H
#define HUELAMPEFFECT_H

#include "fullcoloureffect.h"
#include <QString>

class HueLampEffect : public FullColourEffect
{
private:
    int m_red;
    int m_green;
    int m_blue;

    static const int COLOURMAX = 255;

public:
    HueLampEffect(QString name);

    void calc(int status);
    int getTime(void);
};

#endif // HUELAMPEFFECT_H
