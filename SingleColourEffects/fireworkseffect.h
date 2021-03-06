#ifndef FIREWORKSEFFECT_H
#define FIREWORKSEFFECT_H

#include "SingleColourEffect.h"
#include "particle.h"
#include "constants.h"
#include "cubeTools.h"

class FireworksEffect : public SingleColourEffect
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

#endif // FIREWORKSEFFECT_H
