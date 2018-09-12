#include "array3d.h"

Array3d::Array3d(int arraySize)
{
    m_cubeSize = arraySize;
    m_data = (unsigned char*) malloc(pow(m_cubeSize, 3.0) * sizeof(unsigned char));
}

Array3d::Array3d(const Array3d& obj)
{
    m_cubeSize = obj.m_cubeSize;
    m_data = (unsigned char*) malloc(pow(m_cubeSize, 3.0) * sizeof(unsigned char));

    unsigned char* pdata = m_data;
    unsigned char* pobjData = obj.m_data;

    for(int i = 0; i < pow(m_cubeSize, 3.0); i++)
    {
        *pdata++ = *pobjData++;
    }
}

Array3d::~Array3d()
{
    free(m_data);
}

unsigned char& Array3d::operator()(int x, int y, int z)
{
    if(x >= m_cubeSize || y >= m_cubeSize || z >= m_cubeSize || x < 0 || y < 0 || z < 0)
    {
        std::cout << "invalid pointer: " << x << ", " << y << ", " << z << std::endl;
        return m_data[0];
    }
    return m_data[(x * m_cubeSize + y) * m_cubeSize + z];
}

void Array3d::setAll(unsigned char value)
{
    unsigned char* pdata = m_data;

    for(int i = 0; i < pow(m_cubeSize, 3.0); i++)
    {
        *pdata++ = value;
    }
}

void Array3d::clear(void)
{
    setAll(0);
}
