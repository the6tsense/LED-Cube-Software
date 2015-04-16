#ifndef CUBEWINDOW_H
#define CUBEWINDOW_H

#include "font.h"
#include "texteffect.h"
#include "effecthandler.h"
#include "ui_cubewindow.h"
#include <QPalette>
#include <QMainWindow>
#include <QFile>

using namespace std;

class EffectHandler;

namespace Ui {
class CubeWindow;
}

class CubeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CubeWindow(QWidget *parent = 0);
    ~CubeWindow();

    void setStatus(QString string, QString colour);
    vector<QString> getEffectList(void) const;
    bool isRandomized(void) const;
    unsigned int getEffectSpeed(void) const;

private slots:
    void on_Button_action_toggled(bool checked);

    void on_Button_addAll_clicked();

    void on_Button_deleteAll_clicked();

    void on_Button_add_clicked();

    void on_Button_delete_clicked();

    void on_pushButton_addTextEffect_clicked();

private:
    Ui::CubeWindow* ui;
    EffectHandler* m_effect;
    QButtonGroup* m_colourSelect;
    Font* m_fontAnchor;

    void initComboBox(void);
};

#endif // CUBEWINDOW_H
