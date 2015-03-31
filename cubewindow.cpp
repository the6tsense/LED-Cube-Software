#include "cubewindow.h"

CubeWindow::CubeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CubeWindow)
{
    ui->setupUi(this);
    colourSelect = new QButtonGroup(this);
    colourSelect->addButton(ui->RadioButton_RGB);
    colourSelect->addButton(ui->RadioButton_singleColour);

    initList();
    initComboBox();
}

CubeWindow::~CubeWindow()
{
    delete ui;
}

void CubeWindow::initList(void)
{
    ui->List_effects->addItem("Wave");
    ui->List_effects->addItem("WaveXY");
    ui->List_effects->addItem("WaveMid");
    ui->List_effects->addItem("Plains");
    ui->List_effects->addItem("Rain");
    ui->List_effects->addItem("Waterfall");
    ui->List_effects->addItem("OneAfterAnother");
    ui->List_effects->addItem("randWarpEffect");
    ui->List_effects->addItem("Firework");
    ui->List_effects->addItem("ShrinkBox");
}

void CubeWindow::initComboBox(void)
{
    m_fontAnchor = new Font();
    m_fontAnchor.readFont()
}

//Action button pressed start/stop the animations
void CubeWindow::on_Button_action_toggled(bool checked)
{
    //start animations and block all cube related settings
    if(checked)
    {
        ui->SpinBox_size->setEnabled(false);
        ui->RadioButton_RGB->setEnabled(false);
        ui->RadioButton_singleColour->setEnabled(false);

        //create new effect object
        effect = new EffectHandler(
            ui->SpinBox_size->value(),
            this);

        //try to start animations
        if(!effect->start())
        {
            //port not found
            ui->Button_action->setChecked(false);
            setStatus(QString("Error opening comPort"), QString("#FF0000"));
        }
        else
        {
            //animations started
            setStatus(QString("Running"), QString("#0B610B"));
        }
        return;
    }
    //unblock all cube related settings
    ui->SpinBox_size->setEnabled(true);
    ui->RadioButton_RGB->setEnabled(true);
    ui->RadioButton_singleColour->setEnabled(true);

    setStatus(QString("Stopped"), QString("#868A08"));

    //destroy effect object
    delete(effect);
}

void CubeWindow::on_Button_addAll_clicked()
{
    int size = ui->List_effects->count();

    for(int i = 0; i < size; i++)
    {
        ui->List_executeEffects->addItem(ui->List_effects->takeItem(0));
    }
}

void CubeWindow::on_Button_deleteAll_clicked(void)
{
    int size = ui->List_executeEffects->count();

    for(int i = 0; i < size; i++)
    {
        ui->List_effects->addItem(ui->List_executeEffects->takeItem(0));
    }
}

void CubeWindow::setStatus(QString message, QString colour)
{
    QString temp = tr("<font color = '%1'> %2 </font>");
    ui->Label_status->setText(temp.arg(colour, message));
}

vector<QString> CubeWindow::getEffectList(void) const
{
    int size = ui->List_executeEffects->count();
    vector<QString> out;

    for(int i = 0; i < size; i++)
    {
        out.push_back(ui->List_executeEffects->item(i)->text());
    }

    return out;
}

bool CubeWindow::isRandomized(void) const
{
    return ui->CheckBox_randomize->isChecked();
}

unsigned int CubeWindow::getEffectSpeed(void) const
{
    return floor(pow(10, (double) ui->Slider_effect->value() / 1000));
}

void CubeWindow::on_Button_add_clicked()
{
    ui->List_executeEffects->addItem(ui->List_effects->takeItem(ui->List_effects->currentRow()));
}

void CubeWindow::on_Button_delete_clicked()
{
    ui->List_effects->addItem(ui->List_executeEffects->takeItem(ui->List_executeEffects->currentRow()));
}

void CubeWindow::on_pushButton_addTextEffect_clicked()
{
    Font f;
    f.readFont("C:/Users/Julian/Desktop/DefaultFont.txt");
}
