#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <iostream>
#include <math.h>
#include <stdlib.h>

class Array2d
{
private:
   int m_x;
   int m_y;
   char* data;

public:
   Array2d(int x, int y);
   Array2d(const Array2d& obj);
   ~Array2d();

   char& operator()(int x, int y);
};

#endif // ARRAY2D_H
