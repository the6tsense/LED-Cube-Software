#ifndef CUBEWINDOW_H
#define CUBEWINDOW_H

#include <QMainWindow>
#include "effecthandler.h"
#include "ui_cubewindow.h"
#include <QPalette>

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
    void on_actionButton_toggled(bool checked);

    void on_addAllButton_clicked();

    void on_deleteAllButton_clicked();

    void on_addButton_clicked();

    void on_deletedButton_clicked();

private:
    Ui::CubeWindow* ui;
    EffectHandler* effect;
    QButtonGroup* colourSelect;

    void updatePorts(void);
    void initList(void);
};

#endif // CUBEWINDOW_H
