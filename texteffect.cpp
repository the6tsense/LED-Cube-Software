#include "texteffect.h"

TextEffect::TextEffect(QString name, QString text, int font, int effectType) :
    m_effectName(name),
    m_text(text),
    m_font(font)
{

}

QString TextEffect::getName(void)
{
    return m_effectName;
}
