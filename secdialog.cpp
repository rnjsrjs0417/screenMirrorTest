#include "secdialog.hpp"
#include "ui_secdialog.h"
#include "mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);


}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_clicked()
{
    //hide();
    n=new MainWindow(this);

    n->show();
     n->sampling();
}


void SecDialog::on_pushButton_2_clicked()
{
    quint64 v = QRandomGenerator::global()->bounded(1000, 9999);
   // QMessageBox::about(this,"Number",QString::number(v));

      QMessageBox msg;
      msg.setText(QString::number(v));
      msg.setStyleSheet("QLabel{min-width: 700px;}");

      msg.exec();
}

