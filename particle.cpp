#include "particle.h"

Particle::Particle(int x, int y, int z, double velX, double velY, double velZ, int life) :
    x(x), y(y), z(z), velX(velX), velY(velY), velZ(velZ), life(life), next(nullptr){}


int Particle::getX(void) {
    return (int) floor(x);
}

int Particle::getY(void) {
    return (int) floor(y);
}

int Particle::getZ(void) {
    return (int) floor(z);
}

int Particle::getLife(void) {
    return life;
}

void Particle::setNext(Particle* next) {
    this->next = next;
}

Particle* Particle::getNext(void) {
    return next;
}

void Particle::calc(void) {
    x += velX;
    y += velY;
    z += velZ;

    velZ -= 0.4;
    velX -= 0.6;
    velY -= 0.6;
}
