#ifndef GAMEOFLIFEEFFECT_H
#define GAMEOFLIFEEFFECT_H

#include "SingleColourEffect.h"

class GameOfLifeEffect : public SingleColourEffect
{
public:
    GameOfLifeEffect(QString name);

    int countLivingNeighbors(Array3d& buf, int x, int y, int z);

    void calc(int status);
};

#endif // GAMEOFLIFEEFFECT_H
