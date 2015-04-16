#ifndef TEXTEFFECT_H
#define TEXTEFFECT_H

#include "effect.h"
#include "array2d.h"
#include <QString>

class TextEffect : public Effect
{
private:
    int m_font;
    int m_effectType;
    int m_displayType;
    QString m_text;
    Array2d* m_plane;

public:
    TextEffect(QString name, QString text, int font, int effectType, int displayType);
    ~TextEffect();

    void calc(int status);
    int getTime(void);

    static void outside();
    static void warp();
    static void turn();

    static void stay();
    static void run();
};

#endif // TEXTEFFECT_H
