#include "cubewindow.h"
#include "usbhandler.h"
#include "Array/array2d.h"
#include <QApplication>
#include <thread>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    CubeWindow w;
    w.show();

    return a.exec();
}


