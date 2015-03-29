#ifndef FOREWORKSEFFECT_H
#define FOREWORKSEFFECT_H

#include "effect.h"
#include "particle.h"
#include "constants.h"
#include "cubeTools.h"

class FireworksEffect : public Effect
{
private:
    int m_time;
    int m_zTarget;
    int m_xSource;
    int m_ySource;
    int m_z;
    QString m_key;
    Particle* m_partAnchor;

public:
    FireworksEffect(QString key);

    void calc(int status);
};

#endif // FOREWORKSEFFECT_H
