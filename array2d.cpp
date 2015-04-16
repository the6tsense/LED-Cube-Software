#include "array2d.h"

Array2d::Array2d(int x, int y)
{
    m_x = x;
    m_y = y;
    data = (char*) malloc(x * y * sizeof(char));
}

Array2d::Array2d(const Array2d& obj)
{
    this->m_x = obj.m_x;
    this->m_y = obj.m_y;
    data = (char*) malloc(m_x * m_y * sizeof(char));

    char* pdata = this->data;

    for(int i = 0; i < m_x * m_y; i++)
    {
        *pdata = *(obj.data + i);
    }
}

Array2d::~Array2d()
{
    free(data);
}

char& Array2d::operator()(int x, int y)
{
    if(x >= m_x || y >= m_y || x < 0 || y < 0)
    {
        std::cout << "invalid pointer: " << x << ", " << y << std::endl;
        return data[0];
    }
    return data[x * m_y + y];
}
