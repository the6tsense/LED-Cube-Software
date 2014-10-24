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

void CubeWindow::initList(void) {
    #ifdef __linux__ /*linux*/
    ui->portSelect->addItem("/dev/ttyS0", 0);
    ui->portSelect->addItem("/dev/ttyS1", 1);
    ui->portSelect->addItem("/dev/ttyS2", 2);
    ui->portSelect->addItem("/dev/ttyS3", 3);
    ui->portSelect->addItem("/dev/ttyS4", 4);
    ui->portSelect->addItem("/dev/ttyS5", 5);
    ui->portSelect->addItem("/dev/ttyS6", 6);
    ui->portSelect->addItem("/dev/ttyS7", 7);
    ui->portSelect->addItem("/dev/ttyS8", 8);
    ui->portSelect->addItem("/dev/ttyS9", 9);
    ui->portSelect->addItem("/dev/ttyS10", 10);
    ui->portSelect->addItem("/dev/ttyS11", 11);
    ui->portSelect->addItem("/dev/ttyS12", 12);
    ui->portSelect->addItem("/dev/ttyS13", 13);
    ui->portSelect->addItem("/dev/ttyS14", 14);
    ui->portSelect->addItem("/dev/ttyS15", 15);
    ui->portSelect->addItem("/dev/ttyUSB0", 16);
    ui->portSelect->addItem("/dev/ttyUSB1", 17);
    ui->portSelect->addItem("/dev/ttyUSB2", 18);
    ui->portSelect->addItem("/dev/ttyUSB3", 19);
    ui->portSelect->addItem("/dev/ttyUSB4", 20);
    ui->portSelect->addItem("/dev/ttyUSB5", 21);
    ui->portSelect->addItem("/dev/ttyAMA0", 22);
    ui->portSelect->addItem("/dev/ttyAMA1", 23);
    ui->portSelect->addItem("/dev/ttyACM0", 24);
    ui->portSelect->addItem("/dev/ttyACM1", 25);
    ui->portSelect->addItem("/dev/rfcomm0", 26);
    ui->portSelect->addItem("/dev/rfcomm1", 27);
    ui->portSelect->addItem("/dev/ircomm0", 28);
    ui->portSelect->addItem("/dev/ircomm1", 29);

    #else /*windows*/
    ui->portSelect->addItem("COM1", 0);
    ui->portSelect->addItem("COM2", 1);
    ui->portSelect->addItem("COM3", 2);
    ui->portSelect->addItem("COM4", 3);
    ui->portSelect->addItem("COM5", 4);
    ui->portSelect->addItem("COM6", 5);
    ui->portSelect->addItem("COM7", 6);
    ui->portSelect->addItem("COM8", 7);
    ui->portSelect->addItem("COM9", 8);
    ui->portSelect->addItem("COM10", 9);
    ui->portSelect->addItem("COM11", 10);
    ui->portSelect->addItem("COM12", 11);
    ui->portSelect->addItem("COM13", 12);
    ui->portSelect->addItem("COM14", 13);
    ui->portSelect->addItem("COM15", 14);
    ui->portSelect->addItem("COM16", 15);

    #endif

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
            ui->portSelect->currentIndex(), this);

        //try to start animations
        if(!effect->start()) {
            //port not found
            ui->actionButton->setChecked(false);
            setStatus(QString("Error opening comPort"), QString("#FF0000"));
        } else {
            //animations started
            setStatus(QString("Running"), QString("#0B610B"));
        }
        return;
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
