#ifndef WAVEEFFECT_H
#define WAVEEFFECT_H

class waveEffect : public Effect
{
public:
    waveEffect();

    bool calc(int x, int y, int z, int status);
};
#endif // WAVEEFFECT_H
