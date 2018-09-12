#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();
    int getCubeSize();
    int getCubeColour();

    enum CubeColour {
        COLOUR_SINGLE, COLOUR_GRADIENT, COLOUR_RGB, COLOUR_NONE=-1
    };

private:
    Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_H
