#include "secdialog.hpp"
#include "ui_secdialog.h"
#include "mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "netconnection.h"

NetConnection *net;

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);

    ui->page1->move(0,0);
    ui->page2->move(PAGE_WIDTH,0);

    setWindowFlags(Qt::FramelessWindowHint);

}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_clicked() // 이미 로그인 된 사람 클릭시
{
    n=new MainWindow(this);
    loginComplete(1);
}


void SecDialog::on_pushButton_2_clicked()
{

    QPropertyAnimation *pa1 = new QPropertyAnimation(ui->page1,"geometry");
    QPropertyAnimation *pa2 = new QPropertyAnimation(ui->page2,"geometry");
    pa1->setEasingCurve(QEasingCurve::OutQuint);
    pa1->setDuration(200);
    pa1->setStartValue(ui->page1->geometry());
    pa1->setEndValue(QRect(-PAGE_WIDTH,0,1080,1920));
    pa1->start();

    pa2->setEasingCurve(QEasingCurve::OutQuint);
    pa2->setDuration(200);
    pa2->setStartValue(ui->page2->geometry());
    pa2->setEndValue(QRect(0,0,1080,1920));
    pa2->start();


    NetConnection* net;
    net=new NetConnection(this,"125.6.37.219",&SecDialog::loginComplete);

    QString m = QString::number(net->get_devicecode());
    ui->pwd->setText(m);
    n=new MainWindow(this);

}

void SecDialog::loginComplete(int a)
{
    n->show();
    n->sampling();
}

