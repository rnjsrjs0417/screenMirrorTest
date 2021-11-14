#include "initscreen.h"
#include "mainwindow.h"
#include "ui_initscreen.h"
#include "ui_mainwindow.h"
#include "GBHealth.hpp"
#include "gb_thread.hpp"
#include "lib_header.hpp"
#include "UltraFace.hpp"

initscreen::initscreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initscreen)
{
    ui->setupUi(this);
}

initscreen::~initscreen()
{
    delete ui;
}



void initscreen::on_pushButton_clicked()
{
    hide();
    screen = new MainWindow(this);
    screen->resize(1080,1920);
    screen ->show();
}

