#include "array2d.h"

Array2d::Array2d(int x, int y)
    : m_x(x), m_y(y), m_data(std::vector<std::vector<unsigned char>>(y))
{
    for(; y > 0; y--)
    {
        m_data[y - 1] = std::vector<unsigned char>(x);
    }
}

Array2d::Array2d(const Array2d& obj)
    : m_x(obj.m_x), m_y(obj.m_y), m_data(std::vector<std::vector<unsigned char>>(obj.m_y))
{
    for(int y = 0; y < m_y; y++)
    {
        m_data[y] = std::vector<unsigned char>(m_x);
    }

    for(int x = 0; x < m_x; x++)
    {
        for(int y = 0; y < m_y; y++)
        {
            m_data[y][x] = obj.m_data[y][x];
        }
    }
}

Array2d::~Array2d()
{}

unsigned char& Array2d::operator()(int x, int y)
{
    if(x >= m_x || y >= m_y || x < 0 || y < 0)
    {
        std::cout << "invalid pointer: " << x << ", " << y << std::endl;
        return m_data[0][0];
    }
    return m_data.at(y).at(x);
}

void Array2d::operator<<=(int i)
{
    for(int y = i; y < m_y; y++)
    {
        m_data[y - i] = m_data[y];
    }
}

void Array2d::operator>>=(int i)
{
    for(int y = m_y - i - 1; y >= 0; y--)
    {
        m_data[y + i] = m_data[y];
    }
}

void Array2d::clear(void)
{
    m_data.clear();
}

void Array2d::add(Array2d array, int offx, int offy)
{
    if(array.getHeight() + offx > m_x)
    {
        std::cout << "Array not high enough." << std::endl;
        return;
    }
    if(array.getWidth() + offy > m_y)
    {
        std::cout << "Array not wide enough." << std::endl;
        return;
    }

    for(int x = 0; x < array.getHeight(); x++)
    {
        for(int y = 0; y < array.getWidth(); y++)
        {
            operator()(x + offx, y + offy) = array(x, y);
        }
    }
}

void Array2d::add(const std::vector<unsigned char>& vec, int offx, int offy)
{
    if((int)vec.size() + offx > m_x)
    {
        std::cout << "Array not high enough." << std::endl;
        return;
    }
    if(offy + 1 > m_y)
    {
        std::cout << "Array not wide enough." << std::endl;
        return;
    }

    for(int x = 0; x < (int)vec.size(); x++)
    {
        m_data.at(offy)[offx + x] = vec.at(x);
    }
}

int Array2d::getHeight(void)
{
    return m_x;
}

int Array2d::getWidth(void)
{
    return m_y;
}

std::vector<unsigned char> Array2d::getColumn(int y)
{
    if(y < m_y)
    {
        return m_data[y];
    }
    std::cout << "Illegal column: " << y << std::endl;
    return m_data[0];
}

QString Array2d::toString(void)
{
    QString out;
    for(int x = 0; x < m_x; x++)
    {
        for(int y = 0; y < m_y; y++)
        {
            out.append(QString::number(operator()(x, y)));
            out.append(",");
        }
        out.chop(1);
        out.append("\n");
    }
    return out;
}
