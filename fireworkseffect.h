#ifndef FOREWORKSEFFECT_H
#define FOREWORKSEFFECT_H

#include "effect.h"
#include "particle.h"
#include "constants.h"
#include "cubeTools.h"

class FireworksEffect : public Effect
{
private:
    int m_zTarget;
    int m_xSource;
    int m_ySource;
    int m_z;
    int m_stat;
    Particle* m_partAnchor;

    void deleteParticles(void);

public:
    FireworksEffect(QString key);

    void calc(int status);
    void end(void);
};

#endif // FOREWORKSEFFECT_H
