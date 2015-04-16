#ifndef ARRAY3D_H
#define ARRAY3D_H

#include <iostream>
#include <math.h>
#include <stdlib.h>

class Array3d
{
private:
   int cubeSize;
   bool* data;

public:
   Array3d(int arraySize);
   Array3d(const Array3d& obj);
   ~Array3d();

   bool& operator()(int x, int y, int z);
};

#endif // ARRAY3D_H
