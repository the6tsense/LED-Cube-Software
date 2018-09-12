#ifndef CUBEWINDOW_H
#define CUBEWINDOW_H

#include "font.h"
#include "SingleColourEffects/texteffect.h"
#include "effecthandler.h"
#include "ui_cubewindow.h"
#include "configdialog.h"
#include <QPalette>
#include <QMainWindow>
#include <QFile>

//TODO
#include <QDebug>

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
    void updateAvailableEffects();
    vector<QString> getEffectList(void) const;
    bool isRandomized(void) const;
    int getSelectedColour(void) const;
    unsigned int getEffectSpeed(void) const;

private slots:
    void on_Button_action_toggled(bool checked);
    void on_Button_addAll_clicked();
    void on_Button_deleteAll_clicked();
    void on_Button_add_clicked();
    void on_Button_delete_clicked();
    void on_pushButton_addTextEffect_clicked();

    void on_List_effects_doubleClicked(const QModelIndex &index);
    void on_List_executeEffects_doubleClicked(const QModelIndex &index);

    void on_actionConfigure_triggered();

private:
    Ui::CubeWindow* ui;
    EffectHandler* m_effect;
    Font* m_fontAnchor;

    void initComboBox(void);
};

#endif // CUBEWINDOW_H
