#include "effecthandler.h"

#define MAX_SPEED 1.5

EffectHandler::EffectHandler(int m_cubeSize, CubeWindow* const window) :
    m_status(0),
    cubearray(*(new array3d(m_cubeSize))),
    usb(new usbHandler()),
    mathFunc(new MathFunctions(m_cubeSize))
{

    isActive = true;
    isUpdateReady = false;
    currentEffect = QString("");
    this->m_cubeSize = m_cubeSize;
    this->window = window;

    srand(time(nullptr));

    initAlphabet();

    Tools::clearCube(m_cubeSize, &cubearray);
}

EffectHandler::~EffectHandler() {
    isActive = false;
    for(auto& activeThread : threads) {
        activeThread.join();
    }

    delete usb;
    delete mathFunc;
    delete &cubearray;
}

void EffectHandler::initAlphabet(void) {}

bool EffectHandler::start(void) {
    if(!usb->openPort()) {
        return false;
    }
    threads.push_back(thread(&EffectHandler::effectLoop, this));
    return true;
}

void EffectHandler::effect(void) {
    cout << currentEffect.toStdString() << endl;
    if(!currentEffect.compare("Wave")) {
        waveEffect();

    } else if(!currentEffect.compare("WaveXY")) {
        waveEffectXY();

    } else if(!currentEffect.compare("WaveMid")) {
        waveEffectMid();

    } else if(!currentEffect.compare("Plains")) {
        plainsEffect();

    } else if(!currentEffect.compare("Rain")) {
        rainEffect();

    } else if(!currentEffect.compare("Waterfall")) {
        waterfallEffect();

    } else if(!currentEffect.compare("OneAfterAnother")) {
        oneAfterAnotherEffect();

    } else if(!currentEffect.compare("randWarpEffect")) {
        randWarpEffect();

    } else if(!currentEffect.compare("Firework")) {
        fireworksEffect();

    } else if(!currentEffect.compare("ShrinkBox")) {
        shrinkBoxEffect();

    } else {
        nextEffect();
    }
}

void EffectHandler::effectLoop() {
    Tools::clearCube(m_cubeSize, &cubearray);

    while(isActive) {
        effect();
        //usb->test(true);
        chrono::milliseconds duration(window->getEffectSpeed());
        this_thread::sleep_for(duration);

        usb->sendUpdate(m_cubeSize, &cubearray);
    }
}

void EffectHandler::nextEffect()
{
    vector<QString> effectList = window->getEffectList();
    int size = effectList.size();
    int index = 0;

    cout << "size: " << size << endl;

    //no effects in list
    if(size < 1)
    {
        currentEffect = "";
        Tools::clearCube(m_cubeSize, &cubearray);

    // more than one effect in list
    }
    else if(size > 1)
    {
        Tools::clearCube(m_cubeSize, &cubearray);

        //select random effect
        if(window->isRandomized())
        {
            do
            {
                index = rand() % size;
            }
            while(!effectList[index].compare(currentEffect));

            currentEffect = effectList[index];

        //select next effect from list
        }
        else
        {
            //get index of current effect
            for(auto& item : effectList)
            {
                index++;
                if(!item.compare(currentEffect))
                {
                    break;
                }
            }

            //effect not there anymore or last in list
            //-> new effect = first effect from list
            if(index >= size)
            {
                currentEffect = effectList[0];

            //otherwise select next effect
            }
            else
            {
                currentEffect = effectList[index];
            }
        }
    }
    else
    {
        currentEffect = effectList[0];
    }
}

/******************************** effect functions ************************************/

void EffectHandler::waveEffect(void) {
    mathFunctionEffect(&MathFunctions::linearWave, 100 * M_PI);
}

void EffectHandler::waveEffectXY(void) {
    mathFunctionEffect(&MathFunctions::diagonalWave, 100 * M_PI);
}

void EffectHandler::waveEffectMid(void) {
    mathFunctionEffect(&MathFunctions::midWave, 100 * M_PI);
}

void EffectHandler::plainsEffect(void)
{
    if(m_status == 0)
    {
        switchLayer(0, 0, true);
    }
    else
    {
        switchLayer((m_status - 1) % m_cubeSize, floor((m_status - 1) % (m_cubeSize * 6) / m_cubeSize), false);
        switchLayer(m_status % m_cubeSize, floor(m_status % (m_cubeSize * 6) / m_cubeSize), true);
    }
    m_status++;

    if(m_status > m_cubeSize * 6 * 4)
    {
        m_status = 0;
        nextEffect();
    }
}

void EffectHandler::rainEffect(void) {
    //only every second iteration
    if(m_status % 2) {

        //shift every layer one down
        for(int z = 1; z < m_cubeSize; z++) {
            shiftLayer(z, 0, false);
        }

        //switch off topmost layer
        switchLayer(m_cubeSize - 1, 0, false);

        //select a random number of voxels
        int i = rand() % (int)(pow(m_cubeSize, 2.0) / 7) + m_cubeSize;

        //switch voxels at random locations on
        for(; i > 0; i--) {
            int x = rand() % m_cubeSize;
            int y = rand() % m_cubeSize;
            *cubearray(x, y, m_cubeSize - 1) = true;
        }
    }

    //increase time counter
    m_status++;

    //end effect
    if(m_status > 200) {
        m_status = 0;
        nextEffect();
    }
}

void EffectHandler::waterfallEffect(void) {
    static int x = 0;
    static int y = 0;

    if(m_status == 0) {
        x = rand() % m_cubeSize;
        y = rand() % m_cubeSize;
    }

    //shift every layer one down
    for(int z = 1; z < m_cubeSize; z++) {
        shiftLayer(z, 0, false);
    }

    switchLayer(m_cubeSize - 1, 0, false);

    int randNum = rand() % 3;
    x += randNum - 1;

    randNum = rand() % 3;
    y += randNum - 1;

    //keep x and y coordinates within cube
    if(x < 0) {
        x = 0;
    } else if(x > m_cubeSize - 1) {
        x =  m_cubeSize - 1;
    }
    if(y < 0) {
        y = 0;
    } else if(y > m_cubeSize - 1) {
        y = m_cubeSize - 1;
    }

    *cubearray(x, y, m_cubeSize - 1) = true;
    if((x - 1) >= 0) {
        *cubearray(x - 1, y, m_cubeSize - 1) = true;
    }

    if((x + 1) < m_cubeSize - 1) {
        *cubearray(x + 1, y, m_cubeSize - 1) = true;
    }

    if((y - 1) >= 0) {
        *cubearray(x, y - 1, m_cubeSize - 1) = true;
    }

    if((y + 1) < m_cubeSize - 1) {
        *cubearray(x, y + 1, m_cubeSize - 1) = true;
    }

    m_status++;

    //end effect
    if(m_status > 200) {
        m_status = 0;
        nextEffect();
    }
}

void EffectHandler::randWarpEffect(void) {
    static int side = 0;
    static int* pattern = (int*) malloc(pow(m_cubeSize, 2) * sizeof(int));

    if(m_status % (m_cubeSize * 3) == 0) {
        int newSide = rand() % 6;

        while(newSide == side) {
            newSide = rand() % 6;
        }
        //end effect
        if(m_status > 200) {
            m_status = 0;
            nextEffect();
        }
        side = newSide;

        for(int i = 0; i < pow(m_cubeSize, 2); i++) {
            pattern[i] = rand() % m_cubeSize;
        }
        Tools::clearCube(m_cubeSize, &cubearray);
    }

    if(m_status > m_cubeSize * 3 * 10) {
        m_status = 0;
        nextEffect();
    }

    if(m_status % (m_cubeSize * 3) < m_cubeSize) {
        if(m_status % (m_cubeSize * 3) > 0) {
            for(int x = 0; x < m_cubeSize; x++) {
                for(int y = 0; y < m_cubeSize; y++) {
                    if(pattern[x + y * m_cubeSize]  > m_status % (m_cubeSize * 3) - 1) {
                        *mirror(x, y, (m_status % (m_cubeSize * 3) - 1), side) = false;
                    }
                }
            }
        }
        //iterate through whole plane
        for(int x = 0; x < m_cubeSize; x++) {
            for(int y = 0; y < m_cubeSize; y++) {
                if(pattern[x + y * m_cubeSize] >= m_status % (m_cubeSize * 3)) {
                    *mirror(x, y, m_status % (m_cubeSize * 3), side) = true;
                } else {    //end effect
                    if(m_status > 200) {
                        m_status = 0;
                        nextEffect();
                    }
                    *mirror(x, y, m_status % (m_cubeSize * 3), side) = false;
                }
            }
        }
    } else if(m_status % (m_cubeSize * 3) > 2 * m_cubeSize - 1) {
        if(m_status % (m_cubeSize * 3) > 2 * m_cubeSize) {
            for(int x = 0; x < m_cubeSize; x++) {
                for(int y = 0; y < m_cubeSize; y++) {
                    if(pattern[x + y * m_cubeSize] <= (m_status % (m_cubeSize * 3) - 2 * m_cubeSize - 1)) {
                        *mirror(x, y, (m_status % (m_cubeSize * 3) - 2 * m_cubeSize - 1), side) = false;
                    }
                }
            }
        }
        //iterate through whole plane
        for(int x = 0; x < m_cubeSize; x++) {
            for(int y = 0; y < m_cubeSize; y++) {
                if(pattern[x + y * m_cubeSize] <= (m_status % (m_cubeSize * 3) - 2 * m_cubeSize)) {
                    *mirror(x, y, (m_status % (m_cubeSize * 3) - 2 * m_cubeSize), side) = true;
                } else {
                    *mirror(x, y, (m_status % (m_cubeSize * 3) - 2 * m_cubeSize), side) = false;
                }
            }
        }
    }
    m_status++;
}

void EffectHandler::oneAfterAnotherEffect(void) {
    static int x = 0;
    static int y = 0;
    static int z = 0;

    *cubearray(x, y, z) = true;

    x++;

    if(x >= m_cubeSize) {
        x = 0;
        y++;
    }

    if(y >= m_cubeSize) {
        y = 0;
        z++;
    }

    if(z >= m_cubeSize) {
        x = 0;
        y = 0;
        z = 0;
        nextEffect();
    }
}

void EffectHandler::fireworksEffect(void) {
    static int zTarget;
    static int xSource;
    static int ySource;
    static int z;
    static int iterations = 0;
    static Particle* partAnchor = nullptr;

    if(m_status == 0) {
        zTarget = rand() % (m_cubeSize / 2) + m_cubeSize / 2;
        xSource = rand() % m_cubeSize;
        ySource = rand() % m_cubeSize;
        z = 0;

    } else if(m_status < zTarget) {
        if(z != 0) {
            *cubearray(xSource, ySource, z - 1) = false;
        }
        *cubearray(xSource, ySource, z) = true;
        z++;

    } else if(m_status == zTarget) {
        int particleAmount = rand() % m_cubeSize * 5 + m_cubeSize * 2;
        Particle* part = nullptr;
        Particle* partPrev = nullptr;

        #ifdef DEBUG_FIREWORK
        cout << dec << "particles: "<< particleAmount << endl;
        #endif

        double velX = Tools::randDouble(-MAX_SPEED, MAX_SPEED);
        double velY = Tools::randDouble(-MAX_SPEED, MAX_SPEED);
        double velZ = Tools::randDouble(-MAX_SPEED, MAX_SPEED);
        int life = rand() % (m_cubeSize * 2) + m_cubeSize;
        partAnchor = new Particle(xSource, ySource, zTarget, velX, velY, velZ, life);
        partPrev = partAnchor;

        for(; particleAmount > 0; particleAmount--) {

            velX = Tools::randDouble(-MAX_SPEED, MAX_SPEED);
            velY = Tools::randDouble(-MAX_SPEED, MAX_SPEED);
            velZ = Tools::randDouble(-MAX_SPEED, MAX_SPEED);
            life = rand() % (m_cubeSize * 2) + m_cubeSize;
            part = new Particle(xSource, ySource, zTarget, velX, velY, velZ, life);
            partPrev->setNext(part);
            partPrev = part;

            #ifdef DEBUG_FIREWORK
            cout << dec << velX << ", " << velY << ", " << velZ << ", " << part->getLife() << endl;
            #endif
        }

    } else if(m_status > zTarget) {
        Particle* part = partAnchor;
        bool alife = false;

        Tools::clearCube(m_cubeSize, &cubearray);

        while(part != nullptr) {
            int x = part->getX();
            int y = part->getY();
            int z = part->getZ();

            if(x < 0 || y < 0 || z < 0 ||
                x >= m_cubeSize || y >= m_cubeSize || z >= m_cubeSize
                || part->getLife() < (m_status - zTarget)) {
                part = part->getNext();
                continue;
            }

            alife = true;
            *cubearray(x, y, z) = true;
            part->calc();
            part = part->getNext();
        }

        if(!alife) {
            Particle* part = partAnchor;
            Particle* partNext;

            while(part != nullptr) {
                partNext = part->getNext();
                delete(part);
                part = partNext;
            }

            m_status = -1;
            iterations++;
        }
    }
    m_status++;

    if(iterations > 20) {
        iterations = 0;
        nextEffect();
    }
}


void EffectHandler::shrinkBoxEffect(void)
{
    static int edge;
    static int iterations = 0;

    if(iterations >= 5)
    {
        iterations = 0;
        nextEffect();
    }

    if(m_status == 0)
    {
        edge = rand() % 8;
    }

    Tools::clearCube(m_cubeSize, &cubearray);

    if(m_status < m_cubeSize)
    {
        for(int x = 0; x < m_cubeSize; x++)
        {
            for(int y = 0; y < m_cubeSize; y++)
            {
                for(int z = 0; z < m_cubeSize; z++)
                {
                    if(edge % 2 == 0)
                    {
                        if((x == 0 && y <= m_status && z <= m_status) ||
                           (x <= m_status && y == 0 && z <= m_status) ||
                           (x <= m_status && y <= m_status && z == 0) ||
                           (x == m_status && y <= m_status && z <= m_status) ||
                           (x <= m_status && y == m_status && z <= m_status) ||
                           (x <= m_status && y <= m_status && z == m_status))
                        {
                            *mirror(x, y, z, edge) = true;
                        }
                    }
                    else
                    {
                        if((x == m_cubeSize - 1 && y >= m_status && z >= m_status) ||
                           (x >= m_status && y == m_cubeSize - 1 && z >= m_status) ||
                           (x >= m_status && y >= m_status && z == m_cubeSize - 1) ||
                           (x == m_status && y >= m_status && z >= m_status) ||
                           (x >= m_status && y == m_status && z >= m_status) ||
                           (x >= m_status && y >= m_status && z == m_status))
                        {
                            *mirror(x, y, z, edge - 1) = true;
                        }
                    }
                }
            }
        }
    }
    else if(m_status > m_cubeSize)
    {
        int statNew = m_cubeSize - m_status / 2;
        for(int x = 0; x < m_cubeSize; x++)
        {
            for(int y = 0; y < m_cubeSize; y++)
            {
                for(int z = 0; z < m_cubeSize; z++)
                {
                    if(edge % 2 == 0)
                    {
                        if((x == 0 && y <= statNew && z <= statNew) ||
                           (x <= statNew && y == 0 && z <= statNew) ||
                           (x <= statNew && y <= statNew && z == 0) ||
                           (x == statNew && y <= statNew && z <= statNew) ||
                           (x <= statNew && y == statNew && z <= statNew) ||
                           (x <= statNew && y <= statNew && z == statNew))
                        {
                            *mirror(x, y, z, edge) = true;
                        }
                    }
                    else
                    {
                        if((x == m_cubeSize - 1 && y >= statNew && z >= statNew) ||
                           (x >= statNew && y == m_cubeSize - 1 && z >= statNew) ||
                           (x >= statNew && y >= statNew && z == m_cubeSize - 1) ||
                           (x == statNew && y >= statNew && z >= statNew) ||
                           (x >= statNew && y == statNew && z >= statNew) ||
                           (x >= statNew && y >= statNew && z == statNew))
                        {
                            *mirror(x, y, z, edge - 1) = true;
                        }
                    }
                }
            }
        }
    }
    else if(m_status > m_cubeSize * 2)
    {
        iterations++;
        m_status = -1;
    }
    m_status++;
}

/*void gameOfLifeEffect(void) {
    if(m_status == 0) {
        for(int i = m_cubeSize * 3; i > 0; i--) {
            cubearray();
        }
    } else if(m_status > m_cubeSize * 100) {

    } else {

    }
}*/

/******************************** partial effect functions ****************************/

void EffectHandler::mathFunctionEffect(int (MathFunctions::*function)(int, int, int), int endtime) {
    //clear cube at beginning of each iteration
    Tools::clearCube(m_cubeSize, &cubearray);

    //switch through every led in a Layer
    for(int x = 0; x < m_cubeSize; x++) {
        for(int y = 0; y < m_cubeSize; y++) {

            //calculate x based on function thrown in
            int z = (mathFunc->*function)(x, y, m_status);
            *cubearray(x, y, z) = true;
        }
    }

    //increase time counter
    m_status++;

    //effect reached it's end
    if(m_status == endtime) {
        m_status = 0;
        nextEffect();
    }
}


/******************************** effect helper functions *****************************/

bool* EffectHandler::mirror(int x, int y, int z, int side)
{
    switch(side)
    {
        case 0:
            return cubearray(x, y, z);
            break;
        case 1:
            return cubearray(x, y, m_cubeSize - z - 1);
            break;
        case 2:
            return cubearray(x, z, y);
            break;
        case 3:
            return cubearray(x, m_cubeSize - z - 1, y);
            break;
        case 4:
            return cubearray(z, x, y);
            break;
        case 5:
            return cubearray(m_cubeSize - z - 1, x, y);
            break;
        default:
            std::cout << "Invalid side: " << side << std::endl;
            return cubearray(0, 0, 0);
    }
}

void EffectHandler::switchLayer(int z, int side, bool isOn)
{
    for(int x = 0; x < m_cubeSize; x++)
    {
        for(int y = 0; y < m_cubeSize; y++)
        {
            *mirror(x, y, z, side) = isOn;
        }
    }
}

void EffectHandler::shiftLayer(int z, int side, bool isInvert)
{
    for(int x = 0; x < m_cubeSize; x++)
    {
        for(int y = 0; y < m_cubeSize; y++)
        {
            if(*mirror(x, y, z, side))
            {
                *mirror(x, y, z - 1, side) = !isInvert;
            }
            else
            {
                *mirror(x, y, z - 1, side) = isInvert;
            }
        }
    }
}
