#ifndef LETTER_H
#define LETTER_H

#include "Array/array2d.h"
#include <QString>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

class Letter
{
private:
    int m_width;
    int m_height;
    int m_letterNum;
    std::vector<bool> m_letter;
    Letter* m_next;

public:
    Letter();
    Letter(int width, int height, int letter);
    Letter(int width, int height, int letter, std::vector<bool>* letterArray);
    ~Letter();

    std::vector<bool>* getLetterVector(void);
    Array2d getArray(void);
    int getWidth(void);
    int getHeight(void);
    int getLetterIndex(void);
    void setNext(Letter* next);
    Letter* next(void);

    QString toString(void);
};

#endif // LETTER_H
