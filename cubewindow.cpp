#include "cubewindow.h"

CubeWindow::CubeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CubeWindow) {
    ui->setupUi(this);
    colourSelect = new QButtonGroup(this);
    colourSelect->addButton(ui->RGBrButton);
    colourSelect->addButton(ui->singleColourrButton);

    initList();
}

CubeWindow::~CubeWindow() {
    delete ui;
}

void CubeWindow::updatePorts(void) {
    //the rs232 file has 30 ports for linux to check
    #ifdef __linux__ /*linux*/
    int port = 29;

    //and 16 ports for windows
    #else /*windows*/
    int port = 15;

    #endif

    ui->portSelect->clear();

    //go through all the available ports
    for(; port >= 0; port--)
    {
        //see if a connection can be established
        if(!RS232_OpenComport(port, Constants::BAUDRATE))
        {

#ifdef __linux__
            ui->portSelect->addItem(Constants::linuxPorts[port], port);
#else
            ui->portSelect->addItem("COM" + QString::number(port), port);
#endif

            //and close the connection again
            RS232_CloseComport(port);
        }
    }
}

void CubeWindow::initList(void) {
    updatePorts();

    ui->effectList->addItem("Wave");
    ui->effectList->addItem("WaveXY");
    ui->effectList->addItem("WaveMid");
    ui->effectList->addItem("Plains");
    ui->effectList->addItem("Rain");
    ui->effectList->addItem("Waterfall");
    ui->effectList->addItem("OneAfterAnother");
    ui->effectList->addItem("randWarpEffect");
    ui->effectList->addItem("Firework");
    ui->effectList->addItem("ShrinkBox");
}

//Action button pressed start/stop the animations
void CubeWindow::on_actionButton_toggled(bool checked) {
    //start animations and block all cube related settings
    if(checked) {
        ui->cubeSizeBox->setEnabled(false);
        ui->RGBrButton->setEnabled(false);
        ui->singleColourrButton->setEnabled(false);
        ui->portSelect->setEnabled(false);


        //create new effect object
        effect = new EffectHandler(
            ui->cubeSizeBox->value(),
            ui->portSelect->itemData(0).toInt(), this);

        //try to start animations
        if(!effect->start()) {
            //port not found
            ui->actionButton->setChecked(false);
            setStatus(QString("Error opening comPort"), QString("#FF0000"));

        } else {
            //animations started
            setStatus(QString("Running"), QString("#0B610B"));
            return;
        }
    }
    //unblock all cube related settings
    ui->cubeSizeBox->setEnabled(true);
    ui->RGBrButton->setEnabled(true);
    ui->singleColourrButton->setEnabled(true);
    ui->portSelect->setEnabled(true);

    setStatus(QString("Stopped"), QString("#868A08"));

    //destroy effect object
    delete(effect);
}

void CubeWindow::on_addAllButton_clicked() {
    int size = ui->effectList->count();

    for(int i = 0; i < size; i++) {
        ui->effectExecuteList->addItem(ui->effectList->takeItem(0));
    }
}

void CubeWindow::on_deleteAllButton_clicked(void) {
    int size = ui->effectExecuteList->count();

    for(int i = 0; i < size; i++) {
        ui->effectList->addItem(ui->effectExecuteList->takeItem(0));
    }
}

void CubeWindow::setStatus(QString message, QString colour) {
    QString temp = tr("<font color = '%1'> %2 </font>");
    ui->statusLabel->setText(temp.arg(colour, message));
}

vector<QString> CubeWindow::getEffectList(void) const {
    int size = ui->effectExecuteList->count();
    vector<QString> out;

    for(int i = 0; i < size; i++) {
        out.push_back(ui->effectExecuteList->item(i)->text());
    }

    return out;
}

bool CubeWindow::isRandomized(void) const {
    return ui->randomizeBox->isChecked();
}

unsigned int CubeWindow::getEffectSpeed(void) const {
    return floor(pow(10, (double) ui->effectSlider->value() / 1000));
}

void CubeWindow::on_addButton_clicked() {
    ui->effectExecuteList->addItem(ui->effectList->takeItem(ui->effectList->currentRow()));
}

void CubeWindow::on_deletedButton_clicked() {
    ui->effectList->addItem(ui->effectExecuteList->takeItem(ui->effectExecuteList->currentRow()));
}
