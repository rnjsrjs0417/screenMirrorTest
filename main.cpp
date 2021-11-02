#include "mainwindow.h"
#include "initscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    //initscreen w;
    //w.show();

    MainWindow screen;
    screen.resize(PAGE_WIDTH,PAGE_HEIGHT);
    screen.show();


    return a.exec();
}
