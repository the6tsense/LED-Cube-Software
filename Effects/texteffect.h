#ifndef TEXTEFFECT_H
#define TEXTEFFECT_H

#include "effect.h"
#include "Array/array2d.h"
#include "constants.h"
#include "font.h"
#include <iostream>
#include <QString>

class TextEffect : public Effect
{
private:
    bool m_centered;
    int m_letterSpace;
    int m_effectType;
    int m_displayType;
    int m_textPos;
    Font* m_font;
    QString m_text;
    Array2d* m_plane;

public:
    TextEffect(QString name, QString text, Font* font, int effectType, int displayType,
               bool centered = true, int letterSpace = 1);
    ~TextEffect();

    void calc(int status);
    int getTime(void);
    void end(void);

    void outside();
    void warp();
    void turn();

    void stay();
    void run(bool isRightToLeft);
};

#endif // TEXTEFFECT_H
