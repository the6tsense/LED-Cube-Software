#ifndef EFFECT_H
#define EFFECT_H

#include <stdlib.h>
#include <QString>

class Effect
{
private:
    QString m_key;
    int m_time;

public:
    Effect();
    virtual ~Effect();

    virtual void calc(int status) = 0;
    virtual void end(void);
    void setTime(int time);
    virtual int getTime(void);
    void setKey(QString key);
    QString getKey(void);
};

#endif // EFFECT_H
