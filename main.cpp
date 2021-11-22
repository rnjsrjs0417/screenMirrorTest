#include "mainwindow.h"
#include <QApplication>
#include "secdialog.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    SecDialog b;
    b.show();
    //w.sampling();
    return a.exec();
}

