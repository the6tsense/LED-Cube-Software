#ifndef ARRAY3D_H
#define ARRAY3D_H

#include <iostream>
#include <math.h>
#include <stdlib.h>

class array3d {
private:
   int cubeSize;
   bool* data;

public:
   array3d(int arraySize);
   array3d(const array3d& obj);
   ~array3d();

   bool* operator()(int x, int y, int z);
};

#endif // ARRAY3D_H
