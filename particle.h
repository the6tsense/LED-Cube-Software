#ifndef PARTICLE_H
#define PARTICLE_H

#include <math.h>

class Particle {
private:
    double x;
    double y;
    double z;
    double velX;
    double velY;
    double velZ;
    int life;
    Particle* next;

public:
    Particle(int x, int y, int z, double velX, double velY, double velZ, int life);

    int getX(void);
    int getY(void);
    int getZ(void);

    int getLife(void);
    Particle* getNext(void);
    void setNext(Particle* next);

    void calc(void);
};

#endif // PARTICLE_H
