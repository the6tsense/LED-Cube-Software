#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

#include <QString>

class Array2d
{
private:
   int m_x;
   int m_y;
   std::vector<std::vector<unsigned char>> m_data;

public:
   Array2d(int x, int y);
   Array2d(const Array2d& obj);
   ~Array2d();

   unsigned char& operator()(int x, int y);
   void operator<<=(int i);
   void operator>>=(int i);
   void add(Array2d array, int offx, int offy);
   void add(const std::vector<unsigned char>& vec, int offx, int offy);
   void clear(void);
   int getWidth(void);
   int getHeight(void);
   std::vector<unsigned char> getColumn(int y);
   QString toString(void);
};

#endif // ARRAY2D_H
