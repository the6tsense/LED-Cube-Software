#include "texteffect.h"

TextEffect::TextEffect(QString name, QString text, Font* font, int effectType,
                       int displayType, bool centered, int letterSpace) :
    m_centered(centered),
    m_letterSpace(letterSpace),
    m_effectType(effectType),
    m_displayType(displayType),
    m_textPos(0),
    m_font(font),
    m_text(text),
    m_plane(nullptr)
{
    setKey(name);
}

TextEffect::~TextEffect()
{
    if(m_plane != nullptr)
    {
        delete(m_plane);
    }
}

int TextEffect::getTime(void)
{
    return m_text.size() * Constants::TIMEPERLETTER - 2 * Constants::TIMEPERLETTER;
}

void TextEffect::calc(int status)
{
    if(status == 0)
    {
        if(m_plane == nullptr)
        {
            int x = getCubeSize();
            int y = getCubeSize();

            switch(m_effectType)
            {
                case 0:
                    y *= 4;
                    y -= 4;
                    break;
            }

            m_plane = new Array2d(x, y);
        }

        m_textPos = 0;
    }
    else
    {
        switch(m_displayType)
        {
            case 0:
                run(true);
                break;

            case 1:
                run(false);
                break;

            case 2:
                stay();
                break;

            default:
                std::cout << "Unknown display type: " << m_displayType << std::endl;
        }

        switch(m_effectType)
        {
            case 0:
                outside();
                break;

            case 1:
                warp();
                break;

            case 2:
                turn();
                break;

            default:
                std::cout << "Unknown effect type: " << m_effectType << std::endl;
        }
    }
}

void TextEffect::end(void)
{
    delete(m_plane);
}

void TextEffect::outside(void)
{
    int x = 0;
    int y = 0;
    for(int i = 0; i < m_plane->getWidth(); i++)
    {
        for(int z = 0; z < getCubeSize(); z++)
        {
            cube()(x, y, z) = m_plane->operator()(getCubeSize() - z - 1, i);
        }

        if(i < getCubeSize() - 1)
        {
            x++;
        }
        else if(i < 2 * (getCubeSize() - 1))
        {
            y++;
        }
        else if(i < 3 * (getCubeSize() - 1))
        {
            x--;
        }
        else
        {
            y--;
        }
    }
}

void TextEffect::warp(void)
{

}

void TextEffect::turn(void)
{

}

void TextEffect::stay(void)
{
    int width = 0;
    Letter* currentLetter;
    m_plane->clear();
    while(width < m_plane->getWidth())
    {
        int offMid = 0;
        if(m_centered)
        {
            offMid = (m_plane->getHeight() - currentLetter->getHeight()) / 2;
        }

        m_plane->add(currentLetter->getArray(), offMid, width - currentLetter->getWidth());

        width += m_letterSpace;

        currentLetter = m_font->getLetter(m_text.at(m_textPos++).unicode());

        if(getCubeSize() < currentLetter->getHeight())
        {
            std::cout << "The font " << m_font->getName().toStdString()
                      << " is too high for this cube" << std::endl;
        }
        width += currentLetter->getWidth();
    }
}

void TextEffect::run(bool isRightToLeft)
{
    static int currentColumn = INT_MAX;
    static Array2d currentLetter = Array2d(0, 0);
    int offMid = 0;

    if(currentLetter.getWidth() + m_letterSpace  - 1 < currentColumn && m_text.size() > m_textPos)
    {
        currentLetter = m_font->getLetter(m_text.at(m_textPos).unicode())->getArray();
        m_textPos++;
        currentColumn = 0;
    }
    else if(currentLetter.getWidth() - 1 < currentColumn)
    {
        if(isRightToLeft)
        {
            m_plane->operator <<=(1);
        }
        else
        {
            m_plane->operator >>=(1);
        }
        currentColumn++;
        return;
    }

    if(m_centered)
    {
        offMid = (m_plane->getHeight() - currentLetter.getHeight()) / 2;
    }

    if(isRightToLeft)
    {
        m_plane->operator<<=(1);
        m_plane->add(currentLetter.getColumn(currentColumn), offMid, m_plane->getWidth() - 1);
    }
    else
    {
        m_plane->operator>>=(1);
        m_plane->add(currentLetter.getColumn(currentColumn), offMid, 0);
    }
    currentColumn++;
}
