#include "array3d.h"

array3d::array3d(int arraySize) {
    this->cubeSize = arraySize;
    data = (bool*) malloc(pow(this->cubeSize, 3.0) * sizeof(bool));
}

array3d::array3d(const array3d& obj) {
    this->cubeSize = obj.cubeSize;
    data = (bool*) malloc(pow(cubeSize, 3.0) * sizeof(bool));

    bool* pdata = data;

    for(int i = 0; i < pow(cubeSize, 3.0); i++) {
        *pdata = *(obj.data+i);
    }
}

array3d::~array3d() {
    free(data);
}

bool* array3d::operator()(int x, int y, int z) {
    if(x >= cubeSize || y >= cubeSize || z >= cubeSize || x < 0 || y < 0 || z < 0) {
        std::cout << "invalid pointer: " << x << ", " << y << ", " << z << std::endl;
        return &data[0];
    }
    return &data[x * (int)pow(cubeSize, 2.0) + y * cubeSize + z];
}
