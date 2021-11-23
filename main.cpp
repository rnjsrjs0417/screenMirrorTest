#include "mainwindow.h"
#include <QApplication>
<<<<<<< HEAD
#include <QMessageBox>
#include "secdialog.hpp"
#include "ui_secdialog.h"

=======
#include "secdialog.hpp"
>>>>>>> fbca8041db033b145428070811c624f39f4cb251

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

<<<<<<< HEAD
    //MainWindow w;
    //w.show();
=======

    SecDialog b;
    b.show();
>>>>>>> fbca8041db033b145428070811c624f39f4cb251
    //w.sampling();

    SecDialog w;
    w.show();

    return a.exec();
}

