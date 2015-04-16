#include "fireworkseffect.h"

FireworksEffect::FireworksEffect(QString key) :
    m_stat(0),
    m_partAnchor(nullptr)
{
    setTime(200);
    setKey(key);
}

void FireworksEffect::calc(int status)
{
    Q_UNUSED(status)

    if(m_stat == 0)
    {
        m_zTarget = rand() % (getCubeSize() / 2) + getCubeSize() / 2;
        m_xSource = rand() % getCubeSize();
        m_ySource = rand() % getCubeSize();
        m_z = 0;
    }
    else if(m_stat < m_zTarget)
    {
        if(m_z != 0)
        {
            cube()(m_xSource, m_ySource, m_z - 1) = false;
        }
        cube()(m_xSource, m_ySource, m_z) = true;
        m_z++;
    }
    else if(m_stat == m_zTarget)
    {
        int particleAmount = rand() % getCubeSize() * 5 + getCubeSize() * 2;
        Particle* part = nullptr;
        Particle* partPrev = nullptr;

        #ifdef DEBUG_FIREWORK
        cout << dec << "particles: "<< particleAmount << endl;
        #endif

        double velX = Tools::randDouble(-Constants::MAX_SPEED, Constants::MAX_SPEED);
        double velY = Tools::randDouble(-Constants::MAX_SPEED, Constants::MAX_SPEED);
        double velZ = Tools::randDouble(-Constants::MAX_SPEED, Constants::MAX_SPEED);
        int life = rand() % (getCubeSize() * 2) + getCubeSize();
        m_partAnchor = new Particle(m_xSource, m_ySource, m_zTarget, velX, velY, velZ, life);
        partPrev = m_partAnchor;

        for(; particleAmount > 0; particleAmount--)
        {
            velX = Tools::randDouble(-Constants::MAX_SPEED, Constants::MAX_SPEED);
            velY = Tools::randDouble(-Constants::MAX_SPEED, Constants::MAX_SPEED);
            velZ = Tools::randDouble(-Constants::MAX_SPEED, Constants::MAX_SPEED);
            life = rand() % (getCubeSize() * 2) + getCubeSize();
            part = new Particle(m_xSource, m_ySource, m_zTarget, velX, velY, velZ, life);
            partPrev->setNext(part);
            partPrev = part;

            #ifdef DEBUG_FIREWORK
            cout << dec << velX << ", " << velY << ", " << velZ << ", " << part->getLife() << endl;
            #endif
        }

    }
    else if(m_stat > m_zTarget)
    {
        Particle* part = m_partAnchor;
        bool alife = false;

        clearCube();

        while(part != nullptr)
        {
            int x = part->getX();
            int y = part->getY();
            int z = part->getZ();

            if(x < 0 || y < 0 || z < 0 ||
                x >= getCubeSize() || y >= getCubeSize() || z >= getCubeSize()
                || part->getLife() < (m_stat - m_zTarget))
            {
                part = part->getNext();
                continue;
            }

            alife = true;
            cube()(x, y, z) = true;
            part->calc();
            part = part->getNext();
        }

        if(!alife)
        {
            deleteParticles();

            m_stat = -1;
        }
    }
    m_stat++;
}

void FireworksEffect::end(void)
{
    deleteParticles();
    m_stat = 0;
}

void FireworksEffect::deleteParticles(void)
{
    Particle* part = m_partAnchor;
    Particle* partNext;

    while(part != nullptr)
    {
        partNext = part->getNext();
        delete(part);
        part = partNext;
    }
}
