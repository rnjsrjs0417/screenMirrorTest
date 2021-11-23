#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "secdialog.hpp"
#include "ui_secdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow w;
    //w.show();
    //w.sampling();

    SecDialog w;
    w.show();

    return a.exec();
}

