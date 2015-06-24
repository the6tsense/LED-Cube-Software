#include "letter.h"

Letter::Letter() :
    m_width(0),
    m_height(0),
    m_letterNum(20),
    m_next(nullptr)
{
    m_letter = std::vector<bool>(1);
    m_letter[0] = false;
}

Letter::Letter(int width, int height, int letter, std::vector<bool>* letterArray) :
    m_width(width),
    m_height(height),
    m_letterNum(letter),
    m_letter(*letterArray),
    m_next(nullptr)
{}

Letter::Letter(int width, int height, int letter) :
    m_width(width),
    m_height(height),
    m_letterNum(letter),
    m_letter(*(new std::vector<bool>(width * height))),
    m_next(nullptr)
{}

Letter::~Letter()
{}

std::vector<bool>* Letter::getLetterVector(void)
{
    return &m_letter;
}

Array2d Letter::getArray(void)
{
    Array2d out = Array2d(m_height, m_width);
    int i = 0;

    for(int x = 0; x < m_height; x++)
    {
        for(int y = 0; y < m_width; y++)
        {
            out(x, y) = m_letter[i++];
        }
    }

    return out;
}

int Letter::getWidth(void)
{
    return m_width;
}

int Letter::getHeight(void)
{
    return m_height;
}

int Letter::getLetterIndex(void)
{
    return m_letterNum;
}

void Letter::setNext(Letter* next)
{
    m_next = next;
}

Letter* Letter::next(void)
{
    return m_next;
}

QString Letter::toString(void)
{
    QString out;
    for(int x = 0; x < m_height; x++)
    {
        for(int y = 0; y < m_width; y++)
        {
            if(m_letter[x * m_width + y])
            {
                out.append("1");
            }
            else
            {
                out.append("0");
            }
            out.append(",");
        }
        out.chop(1);
        out.append("\n");
    }

    return out;
}
