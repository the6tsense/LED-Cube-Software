#include "effecthandler.h"

#define MAX_SPEED 1.5

EffectHandler::EffectHandler(int cubeSize, int comPort, CubeWindow* const window) :
    cubearray(*(new array3d(cubeSize))),
    usb(new usbHandler(comPort)),
    mathFunc(new MathFunctions(cubeSize)) {

    isActive = true;
    isUpdateReady = false;
    currentEffect = QString("");
    this->cubeSize = cubeSize;
    this->window = window;

    srand(time(nullptr));

    initAlphabet();

    Tools::clearCube(cubeSize, &cubearray);
}

EffectHandler::~EffectHandler() {
    isActive = false;
    for(auto& activeThread : threads) {
        activeThread.join();
    }
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
    Tools::clearCube(cubeSize, &cubearray);

    while(isActive) {
        effect();
        //usb->test(true);
        chrono::milliseconds duration(window->getEffectSpeed());
        this_thread::sleep_for(duration);

        usb->sendUpdate(cubeSize, &cubearray);
    }
}

void EffectHandler::nextEffect() {
    vector<QString> effectList = window->getEffectList();
    int size = effectList.size();
    int index = 0;

    cout << "size: " << size << endl;

    //no effects in list
    if(size < 1) {
        currentEffect = "";
        Tools::clearCube(cubeSize, &cubearray);

    // more than one effect in list
    } else if(size > 1) {
        Tools::clearCube(cubeSize, &cubearray);

        //select random effect
        if(window->isRandomized()) {
            do {
                index = rand() % size;
            } while(!effectList[index].compare(currentEffect));

            currentEffect = effectList[index];

        //select next effect from list
        } else {
            //get index of current effect
            for(auto& item : effectList) {
                index++;
                if(!item.compare(currentEffect)) {
                    break;
                }
            }

            //effect not there anymore or last in list
            //-> new effect = first effect from list
            if(index >= size) {
                currentEffect = effectList[0];

            //otherwise select next effect
            } else {
                currentEffect = effectList[index];
            }
        }
    } else if(!currentEffect.compare("")) {
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

void EffectHandler::plainsEffect(void) {
    switchLayer((status - 1) % cubeSize, floor((status - 1) % (cubeSize * 6) / cubeSize), false);
    switchLayer(status % cubeSize, floor(status % (cubeSize * 6) / cubeSize), true);
    status++;

    if(status > cubeSize * 6 * 4) {
        status = 0;
        nextEffect();
    }
}

void EffectHandler::rainEffect(void) {
    //only every second iteration
    if(status % 2) {

        //shift every layer one down
        for(int z = 1; z < cubeSize; z++) {
            shiftLayer(z, 0, false);
        }

        //switch off topmost layer
        switchLayer(cubeSize - 1, 0, false);

        //select a random number of voxels
        int i = rand() % (int)(pow(cubeSize, 2.0) / 7) + cubeSize;

        //switch voxels at random locations on
        for(; i > 0; i--) {
            int x = rand() % cubeSize;
            int y = rand() % cubeSize;
            *cubearray(x, y, cubeSize - 1) = true;
        }
    }

    //increase time counter
    status++;

    //end effect
    if(status > 200) {
        status = 0;
        nextEffect();
    }
}

void EffectHandler::waterfallEffect(void) {
    static int x = 0;
    static int y = 0;

    if(status == 0) {
        x = rand() % cubeSize;
        y = rand() % cubeSize;
    }

    //shift every layer one down
    for(int z = 1; z < cubeSize; z++) {
        shiftLayer(z, 0, false);
    }

    switchLayer(cubeSize - 1, 0, false);

    int randNum = rand() % 3;
    x += randNum - 1;

    randNum = rand() % 3;
    y += randNum - 1;

    //keep x and y coordinates within cube
    if(x < 0) {
        x = 0;
    } else if(x > cubeSize - 1) {
        x =  cubeSize - 1;
    }
    if(y < 0) {
        y = 0;
    } else if(y > cubeSize - 1) {
        y = cubeSize - 1;
    }

    *cubearray(x, y, cubeSize - 1) = true;
    if((x - 1) >= 0) {
        *cubearray(x - 1, y, cubeSize - 1) = true;
    }

    if((x + 1) < cubeSize - 1) {
        *cubearray(x + 1, y, cubeSize - 1) = true;
    }

    if((y - 1) >= 0) {
        *cubearray(x, y - 1, cubeSize - 1) = true;
    }

    if((y + 1) < cubeSize - 1) {
        *cubearray(x, y + 1, cubeSize - 1) = true;
    }

    status++;

    //end effect
    if(status > 200) {
        status = 0;
        nextEffect();
    }
}

void EffectHandler::randWarpEffect(void) {
    static int side = 0;
    static int* pattern = (int*) malloc(pow(cubeSize, 2) * sizeof(int));

    if(status % (cubeSize * 3) == 0) {
        int newSide = rand() % 6;

        while(newSide == side) {
            newSide = rand() % 6;
        }
        //end effect
        if(status > 200) {
            status = 0;
            nextEffect();
        }
        side = newSide;

        for(int i = 0; i < pow(cubeSize, 2); i++) {
            pattern[i] = rand() % cubeSize;
        }
        Tools::clearCube(cubeSize, &cubearray);
    }

    if(status > cubeSize * 3 * 10) {
        status = 0;
        nextEffect();
    }

    if(status % (cubeSize * 3) < cubeSize) {
        if(status % (cubeSize * 3) > 0) {
            for(int x = 0; x < cubeSize; x++) {
                for(int y = 0; y < cubeSize; y++) {
                    if(pattern[x + y * cubeSize]  > status % (cubeSize * 3) - 1) {
                        *mirror(x, y, (status % (cubeSize * 3) - 1), side) = false;
                    }
                }
            }
        }
        //iterate through whole plane
        for(int x = 0; x < cubeSize; x++) {
            for(int y = 0; y < cubeSize; y++) {
                if(pattern[x + y * cubeSize] >= status % (cubeSize * 3)) {
                    *mirror(x, y, status % (cubeSize * 3), side) = true;
                } else {    //end effect
                    if(status > 200) {
                        status = 0;
                        nextEffect();
                    }
                    *mirror(x, y, status % (cubeSize * 3), side) = false;
                }
            }
        }
    } else if(status % (cubeSize * 3) > 2 * cubeSize - 1) {
        if(status % (cubeSize * 3) > 2 * cubeSize) {
            for(int x = 0; x < cubeSize; x++) {
                for(int y = 0; y < cubeSize; y++) {
                    if(pattern[x + y * cubeSize] <= (status % (cubeSize * 3) - 2 * cubeSize - 1)) {
                        *mirror(x, y, (status % (cubeSize * 3) - 2 * cubeSize - 1), side) = false;
                    }
                }
            }
        }
        //iterate through whole plane
        for(int x = 0; x < cubeSize; x++) {
            for(int y = 0; y < cubeSize; y++) {
                if(pattern[x + y * cubeSize] <= (status % (cubeSize * 3) - 2 * cubeSize)) {
                    *mirror(x, y, (status % (cubeSize * 3) - 2 * cubeSize), side) = true;
                } else {
                    *mirror(x, y, (status % (cubeSize * 3) - 2 * cubeSize), side) = false;
                }
            }
        }
    }
    status++;
}

void EffectHandler::oneAfterAnotherEffect(void) {
    static int x = 0;
    static int y = 0;
    static int z = 0;

    *cubearray(x, y, z) = true;

    x++;

    if(x >= cubeSize) {
        x = 0;
        y++;
    }

    if(y >= cubeSize) {
        y = 0;
        z++;
    }

    if(z >= cubeSize) {
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

    if(status == 0) {
        zTarget = rand() % (cubeSize / 2) + cubeSize / 2;
        xSource = rand() % cubeSize;
        ySource = rand() % cubeSize;
        z = 0;

    } else if(status < zTarget) {
        if(z != 0) {
            *cubearray(xSource, ySource, z - 1) = false;
        }
        *cubearray(xSource, ySource, z) = true;
        z++;

    } else if(status == zTarget) {
        int particleAmount = rand() % cubeSize * 5 + cubeSize * 2;
        Particle* part = nullptr;
        Particle* partPrev = nullptr;

        cout << dec << "particles: "<< particleAmount << endl;

        double velX = Tools::randDouble(-MAX_SPEED, MAX_SPEED);
        double velY = Tools::randDouble(-MAX_SPEED, MAX_SPEED);
        double velZ = Tools::randDouble(-MAX_SPEED, MAX_SPEED);
        int life = rand() % (cubeSize * 2) + cubeSize;
        partAnchor = new Particle(xSource, ySource, zTarget, velX, velY, velZ, life);
        partPrev = partAnchor;

        for(; particleAmount > 0; particleAmount--) {

            velX = Tools::randDouble(-MAX_SPEED, MAX_SPEED);
            velY = Tools::randDouble(-MAX_SPEED, MAX_SPEED);
            velZ = Tools::randDouble(-MAX_SPEED, MAX_SPEED);
            life = rand() % (cubeSize * 2) + cubeSize;
            part = new Particle(xSource, ySource, zTarget, velX, velY, velZ, life);
            partPrev->setNext(part);
            partPrev = part;
            cout << dec << velX << ", " << velY << ", " << velZ << ", " << part->getLife() << endl;

        }

    } else if(status > zTarget) {
        cout << partAnchor << endl;
        Particle* part = partAnchor;
        bool alife = false;

        Tools::clearCube(cubeSize, &cubearray);

        while(part != nullptr) {
            int x = part->getX();
            int y = part->getY();
            int z = part->getZ();

            if(x < 0 || y < 0 || z < 0 ||
                x >= cubeSize || y >= cubeSize || z >= cubeSize
                || part->getLife() < (status - zTarget)) {
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

            cout << "DEAD" << endl;

            while(part != nullptr) {
                partNext = part->getNext();
                delete(part);
                part = partNext;
            }

            status = -1;
            iterations++;
        }
    }
    status++;

    if(iterations > 5) {
        iterations = 0;
        nextEffect();
    }
}


void EffectHandler::shrinkBoxEffect(void) {
    static int edge;
    static int iterations = 0;

    if(iterations >= 5) {
        iterations = 0;
        nextEffect();
    }

    if(status == 0) {
        edge = rand() % 8;
    }

    Tools::clearCube(cubeSize, &cubearray);

    if(status < cubeSize) {
        for(int x = 0; x < cubeSize; x++) {
            for(int y = 0; y < cubeSize; y++) {
                for(int z = 0; z < cubeSize; z++) {
                    if(edge % 2 == 0) {
                        if((x == 0 && y <= status && z <= status) ||
                           (x <= status && y == 0 && z <= status) ||
                           (x <= status && y <= status && z == 0) ||
                           (x == status && y <= status && z <= status) ||
                           (x <= status && y == status && z <= status) ||
                           (x <= status && y <= status && z == status)) {
                            *mirror(x, y, z, edge) = true;
                        }
                    } else {
                        if((x == cubeSize - 1 && y >= status && z >= status) ||
                           (x >= status && y == cubeSize - 1 && z >= status) ||
                           (x >= status && y >= status && z == cubeSize - 1) ||
                           (x == status && y >= status && z >= status) ||
                           (x >= status && y == status && z >= status) ||
                           (x >= status && y >= status && z == status)) {
                            *mirror(x, y, z, edge - 1) = true;
                        }
                    }
                }
            }
       }
    } else if(status > cubeSize) {
        int statNew = cubeSize - status / 2;
        for(int x = 0; x < cubeSize; x++) {
            for(int y = 0; y < cubeSize; y++) {
                for(int z = 0; z < cubeSize; z++) {
                    if(edge % 2 == 0) {
                        if((x == 0 && y <= statNew && z <= statNew) ||
                           (x <= statNew && y == 0 && z <= statNew) ||
                           (x <= statNew && y <= statNew && z == 0) ||
                           (x == statNew && y <= statNew && z <= statNew) ||
                           (x <= statNew && y == statNew && z <= statNew) ||
                           (x <= statNew && y <= statNew && z == statNew)) {
                            *mirror(x, y, z, edge) = true;
                        }

                    } else {
                        if((x == cubeSize - 1 && y >= statNew && z >= statNew) ||
                           (x >= statNew && y == cubeSize - 1 && z >= statNew) ||
                           (x >= statNew && y >= statNew && z == cubeSize - 1) ||
                           (x == statNew && y >= statNew && z >= statNew) ||
                           (x >= statNew && y == statNew && z >= statNew) ||
                           (x >= statNew && y >= statNew && z == statNew)) {
                            *mirror(x, y, z, edge - 1) = true;
                        }
                    }
                }
            }
        }

    } else if(status > cubeSize * 2) {
        iterations++;
        status = -1;
    }
    status++;
}

/*void EffectHandler::gameOfLifeEffect(void) {
    if(status == 0) {
        for(int i = cubeSize * 3; i > 0; i--) {
            *cubearray(x,y,yz);
        }
    } else if(status > cubeSize * 100) {

    } else {

    }
}*/

/******************************** partial effect functions ****************************/

void EffectHandler::mathFunctionEffect(int (MathFunctions::*function)(int, int, int), int endtime) {
    //clear cube at beginning of each iteration
    Tools::clearCube(cubeSize, &cubearray);

    //switch through every led in a Layer
    for(int x = 0; x < cubeSize; x++) {
        for(int y = 0; y < cubeSize; y++) {

            //calculate x based on function thrown in
            int z = (mathFunc->*function)(x, y, status);
            *cubearray(x, y, z) = true;
        }
    }

    //increase time counter
    status++;

    //effect reached it's end
    if(status == endtime) {
        status = 0;
        nextEffect();
    }
}


/******************************** effect helper functions *****************************/

bool* EffectHandler::mirror(int x, int y, int z, int side) {
    if(x < 0 || x >= cubeSize || y < 0 || y >= cubeSize || z < 0 || z >= cubeSize) {
        cout << "invalid pointer" << endl;
        return nullptr;
    }

    switch(side) {
        case 0:
            return cubearray(x, y, z);
            break;
        case 1:
            return cubearray(x, y, cubeSize - z - 1);
            break;
        case 2:
            return cubearray(x, z, y);
            break;
        case 3:
            return cubearray(x, cubeSize - z - 1, y);
            break;
        case 4:
            return cubearray(z, x, y);
            break;
        case 5:
            return cubearray(cubeSize - z - 1, x, y);
            break;
        default:
            cout << "invalid side" << endl;
            return nullptr;
    }
}

void EffectHandler::switchLayer(int z, int side, bool isOn) {
    for(int x = 0; x < cubeSize; x++) {
        for(int y = 0; y < cubeSize; y++) {
            *mirror(x, y, z, side) = isOn;
        }
    }
}

void EffectHandler::shiftLayer(int z, int side, bool isInvert) {
    for(int x = 0; x < cubeSize; x++) {
        for(int y = 0; y < cubeSize; y++) {
            if(*mirror(x, y, z, side)) {
                *mirror(x, y, z - 1, side) = !isInvert;
            } else {
                *mirror(x, y, z - 1, side) = isInvert;
            }
        }
    }
}
