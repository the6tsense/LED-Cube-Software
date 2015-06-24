#include "effecthandler.h"

EffectHandler::EffectHandler(CubeWindow* const window) :
    m_status(0),
    m_usb(new UsbHandler()),
    m_currentEffect(nullptr)
{
    m_isActive = true;
    m_isUpdateReady = false;
    m_window = window;

    srand(time(nullptr));

    initEffectList();

    Effect::clearCube();
}

EffectHandler::~EffectHandler()
{
    stop();
    for(auto& effect : m_effects)
    {
        delete(effect);
    }
}

void EffectHandler::initEffectList(void)
{
    m_effects.push_back(new FireworksEffect("Fireworks"));
    m_effects.push_back(new OneAfterAnotherEffect("One after another"));
    m_effects.push_back(new PlainsEffect("Plains"));
    m_effects.push_back(new RainEffect("Rain"));
    m_effects.push_back(new RandWarpEffect("Random warp"));
    m_effects.push_back(new ShrinkBoxEffect("Shrink Box"));
    m_effects.push_back(new WaterfallEffect("Waterfall"));
    m_effects.push_back(new MathFunctionEffect(3.14159 * 100, "Wave", &MathFunctions::linearWave));
    m_effects.push_back(new MathFunctionEffect(3.14159 * 100,
                                               "Diagonal Wave",
                                               &MathFunctions::diagonalWave));
    m_effects.push_back(new MathFunctionEffect(3.14159 * 100,
                                               "Middle Wave",
                                               &MathFunctions::midWave));
}

bool EffectHandler::start(void)
{
    if(!m_usb->openPort())
    {
        return false;
    }

    m_isActive = true;
    m_threads.push_back(thread(&EffectHandler::effectLoop, this));
    return true;
}

void EffectHandler::stop(void)
{
    m_isActive = false;
    for(auto& activeThread : m_threads)
    {
        activeThread.join();
    }
    m_threads.clear();

    m_currentEffect = nullptr;
    m_status = 0;
    delete(m_usb);
}

void EffectHandler::addEffect(Effect* effect)
{
    m_effects.push_back(effect);
}

vector<QString> EffectHandler::getEffects(void)
{
    vector<QString> out;

    for(auto& effect : m_effects)
    {
        out.push_back((*effect).getKey());
    }
    return out;
}

void EffectHandler::effectLoop()
{
    Effect::clearCube();

    while(m_isActive)
    {
        if(m_currentEffect == nullptr)
        {
            nextEffect();
            chrono::milliseconds duration(20);
            this_thread::sleep_for(duration);
            continue;
        }

        m_currentEffect->calc(m_status);

        //usb->test(true);
        chrono::milliseconds duration(m_window->getEffectSpeed());
        this_thread::sleep_for(duration);

        m_usb->sendUpdate();

        m_status++;

        if(m_status >= m_currentEffect->getTime())
        {
            m_status = 0;
            nextEffect();
        }
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
        if(m_currentEffect != nullptr)
        {
            m_currentEffect->end();
        }
        m_currentEffect = nullptr;

        Effect::clearCube();
        m_usb->sendUpdate();

        return;
    }

    // more than one effect in list
    if(size > 1)
    {
        if(m_currentEffect == nullptr)
        {
            if(m_window->isRandomized())
            {
                index = rand() % size;
            }
            else
            {
                index = 0;
            }
        }
        else
        {
            m_currentEffect->end();

            Effect::clearCube();

            //select random effect
            if(m_window->isRandomized())
            {
                do
                {
                    index = rand() % size;
                }
                while(!effectList[index].compare(m_currentEffect->getKey()));
            }
            //select next effect from list
            else
            {
                //get index of current effect
                for(auto& item : effectList)
                {
                    index++;
                    if(!item.compare(m_currentEffect->getKey()))
                    {
                        break;
                    }
                }

                //effect not there anymore or last in list
                //-> new effect = first effect from list
                if(index >= size)
                {
                    index = 0;
                }
            }
        }
    }
    else
    {
        index = 0;
    }

    for(auto& effect : m_effects)
    {
        if(!effect->getKey().compare(effectList[index]))
        {
            m_currentEffect = effect;
            return;
        }
    }

    std::cout << "Effect not there." << std::endl;
}



