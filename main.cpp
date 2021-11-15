#include "mainwindow.h"
#include "initscreen.h"
#include <QFontDatabase>
#include <QApplication>
#include "GBHealth.hpp"
#include "gb_thread.hpp"
#include "lib_header.hpp"
#include "UltraFace.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    initscreen w;
    w.show();
    QApplication application(argc, argv);


//    MainWindow screen;
//    screen.resize(PAGE_WIDTH,PAGE_HEIGHT);
//    screen.show();




    return a.exec();
}
