#ifndef GAMEOFLIFEEFFECT_H
#define GAMEOFLIFEEFFECT_H

#include "effect.h"

class GameOfLifeEffect : public Effect
{
public:
    GameOfLifeEffect(QString name);

    int countLivingNeighbors(Array3d& buf, int x, int y, int z);

    void calc(int status);
};

#endif // GAMEOFLIFEEFFECT_H
