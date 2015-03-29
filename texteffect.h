#ifndef TEXTEFFECT_H
#define TEXTEFFECT_H

#include <QString>

class TextEffect
{
private:
    QString m_effectName;
    QString m_text;
    int m_font;
    int m_effectType;

public:
    TextEffect(QString name, QString text, int font, int effectType);

    QString getName(void);
};

#endif // TEXTEFFECT_H
