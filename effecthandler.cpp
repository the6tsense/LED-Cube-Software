#include "effecthandler.h"

EffectHandler::EffectHandler(CubeWindow* const window) :
    m_status(0),
    m_usb(new usbHandler())
{
    m_isActive = true;
    m_isUpdateReady = false;
    m_currentEffect = QString("");
    m_window = window;

    srand(time(nullptr));

    initEffectList();

    Effect::clearCube();
}

EffectHandler::~EffectHandler()
{
    m_isActive = false;
    for(auto& activeThread : m_threads)
    {
        activeThread.join();
    }

    delete m_usb;
}

void EffectHandler::initEffectList(void)
{
    m_effects.push_back(new FireworksEffect("Fireworks"));
}

bool EffectHandler::start(void)
{
    if(!m_usb->openPort())
    {
        return false;
    }
    m_threads.push_back(thread(&EffectHandler::effectLoop, this));
    return true;
}

void EffectHandler::effect(void)
{
    /*cout << currentEffect.toStdString() << endl;
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
    }*/
}

void EffectHandler::effectLoop()
{
    Effect::clearCube();

    while(m_isActive)
    {
        effect();
        //usb->test(true);
        chrono::milliseconds duration(m_window->getEffectSpeed());
        this_thread::sleep_for(duration);

        m_usb->sendUpdate();
    }
}

void EffectHandler::nextEffect()
{
    vector<QString> effectList = m_window->getEffectList();
    int size = effectList.size();
    int index = 0;

    cout << "size: " << size << endl;

    //no effects in list
    if(size < 1)
    {
        m_currentEffect = "";
        Effect::clearCube();

    // more than one effect in list
    }
    else if(size > 1)
    {
        Effect::clearCube();

        //select random effect
        if(m_window->isRandomized())
        {
            do
            {
                index = rand() % size;
            }
            while(!effectList[index].compare(m_currentEffect));

            m_currentEffect = effectList[index];

        //select next effect from list
        }
        else
        {
            //get index of current effect
            for(auto& item : effectList)
            {
                index++;
                if(!item.compare(m_currentEffect))
                {
                    break;
                }
            }

            //effect not there anymore or last in list
            //-> new effect = first effect from list
            if(index >= size)
            {
                m_currentEffect = effectList[0];

            //otherwise select next effect
            }
            else
            {
                m_currentEffect = effectList[index];
            }
        }
    }
    else
    {
        m_currentEffect = effectList[0];
    }
}

/******************************** effect functions ************************************/

/*void gameOfLifeEffect(void) {
    if(m_status == 0) {
        for(int i = m_cubeSize * 3; i > 0; i--) {
            cubearray();
        }
    } else if(m_status > m_cubeSize * 100) {

    } else {

    }
}*/



