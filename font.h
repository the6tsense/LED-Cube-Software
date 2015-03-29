#ifndef FONTS_H
#define FONTS_H

#include "letter.h"
#include <QString>
#include <fstream>
#include <iostream>
#include <vector>

class Font
{
private:
    static int s_fontAmount;

    int m_letterAmount;
    QString m_fontName;
    Letter* m_font;
    Font* m_next;

public:
    Font();
    ~Font();

    Letter* getLetter(int letter);

    /*
     * returns: 0 for success, 1 for unknown xml command, 2 for width/height not found
     *          3 for wrong stage,
     */
    int readFont(QString filepath);
};

#endif // FONTS_H
