#ifndef GAMEOFLIFEEFFECT_H
#define GAMEOFLIFEEFFECT_H

#include "effect.h"

class GameOfLifeEffect : public Effect
{
public:
    GameOfLifeEffect(QString name);

    void calc(int status);
};

#endif // GAMEOFLIFEEFFECT_H
