#include "liardetector.h"
#include "ui_liardetector.h"
#include "mainwindow.h"

liarDetector::liarDetector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::liarDetector)
{
    ui->setupUi(this);
}

liarDetector::~liarDetector()
{
    delete ui;
}

void liarDetector::on_pushButton_clicked()
{
    this->close();
    MainWindow w;
    w.show();
}

