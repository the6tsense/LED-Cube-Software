#ifndef TEXTEFFECT_H
#define TEXTEFFECT_H

#include <QString>

class TextEffect
{
private:
    QString m_effectName;
    QString m_text;
    int m_font;

public:
    TextEffect(QString name, QString text, int font);
};

#endif // TEXTEFFECT_H
