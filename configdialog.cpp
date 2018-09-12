#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

int ConfigDialog::getCubeSize()
{
    return ui->spinBox->value();
}

int ConfigDialog::getCubeColour()
{
    if(ui->radioButton_Single->isChecked())
    {
        return COLOUR_SINGLE;
    }
    else if(ui->radioButton_Gradient->isChecked())
    {
        return COLOUR_GRADIENT;
    }
    else if(ui->radioButton_RGB->isChecked())
    {
        return COLOUR_RGB;
    }

    return COLOUR_NONE;
}
