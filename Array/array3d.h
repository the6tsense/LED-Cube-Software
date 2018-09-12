#ifndef ARRAY3D_H
#define ARRAY3D_H

#include <iostream>
#include <math.h>
#include <stdlib.h>

class Array3d
{
private:
   int m_cubeSize;
   unsigned char* m_data;

public:
   Array3d(int arraySize);
   Array3d(const Array3d& obj);
   ~Array3d();

   unsigned char& operator()(int x, int y, int z);
   void setAll(unsigned char value);
   void clear();
};

#endif // ARRAY3D_H
