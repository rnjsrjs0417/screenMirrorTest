#include "mainwindow.h"
#include "initscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    //MainWindow w;
    initscreen w;

    //w.resize(1080,1920);
    w.show();


    return a.exec();
}
