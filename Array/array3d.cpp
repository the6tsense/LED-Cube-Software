#include "array3d.h"

Array3d::Array3d(int arraySize)
{
    this->cubeSize = arraySize;
    data = (bool*) malloc(pow(this->cubeSize, 3.0) * sizeof(bool));
}

Array3d::Array3d(const Array3d& obj)
{
    this->cubeSize = obj.cubeSize;
    data = (bool*) malloc(pow(cubeSize, 3.0) * sizeof(bool));

    bool* pdata = data;
    bool* pobjData = obj.data;

    for(int i = 0; i < pow(cubeSize, 3.0); i++)
    {
        *pdata++ = *pobjData++;
    }
}

Array3d::~Array3d()
{
    free(data);
}

bool& Array3d::operator()(int x, int y, int z)
{
    if(x >= cubeSize || y >= cubeSize || z >= cubeSize || x < 0 || y < 0 || z < 0)
    {
        std::cout << "invalid pointer: " << x << ", " << y << ", " << z << std::endl;
        return data[0];
    }
    return data[x * (int)pow(cubeSize, 2.0) + y * cubeSize + z];
}
