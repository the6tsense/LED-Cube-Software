#include "effect.h"

Effect::Effect()
{}

Effect::~Effect()
{}

void Effect::end(void)
{}

void Effect::setTime(int time)
{
    m_time = time;
}

int Effect::getTime(void)
{
    return m_time;
}

void Effect::setKey(QString key)
{
    m_key = key;
}

QString Effect::getKey(void)
{
    return m_key;
}
