#include "texteffect.h"

TextEffect::TextEffect(QString name, QString text, int font, int effectType, int displayType) :
    m_font(font),
    m_effectType(effectType),
    m_displayType(displayType),
    m_text(text),
    m_plane(nullptr)
{
    int x = getCubeSize();
    int y = getCubeSize();
    setKey(name);

    switch(m_effectType)
    {
        case 0:
            x *= 4;
            break;
    }

    m_plane = new Array2d(x, y);
}

TextEffect::~TextEffect()
{
    delete(m_plane);
}

int TextEffect::getTime(void)
{
    //calculate time
    return 200;
}

void TextEffect::calc(int status)
{
    switch(m_displayType)
    {
        case 0:
            run();
            break;

        case 1:
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

void TextEffect::outside()
{

}

void TextEffect::warp()
{

}

void TextEffect::turn()
{

}

void TextEffect::stay()
{

}

void TextEffect::run()
{
    QRefString()
}
