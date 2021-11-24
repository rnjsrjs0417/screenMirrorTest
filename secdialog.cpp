#include "secdialog.hpp"
#include "ui_secdialog.h"
#include "mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include "netconnection.h"
#include <QFile>

NetConnection *net;

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);

    ui->page1->move(0,0);
    ui->page2->move(PAGE_WIDTH,0);

    setWindowFlags(Qt::FramelessWindowHint);


    name[0] = "+"; name[1] = "+"; name[2] = "+";
    id[0] = ""; id[1] = ""; id[2] = "";
    // LOAD user info with txt file communication
    loadUserInfo();


}

SecDialog::~SecDialog()
{
    delete ui;
}


void SecDialog::loadUserInfo()
{
    //debug code
    name[1] = "은구"; name[2] = "+"; name[3] = "+";
    id[1] = "dmsrn135"; id[2] = ""; id[3] = "";

    //file input
    QFile file("C:\\Users\\Kwon Geon\\Documents\\GitHub\\screenMirrorTest\\userInfo.txt");

    if( !file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }

    QTextStream in(&file);
    QString text =

    //label set
    ui->pushButton->setText(name[1]);
    ui->pushButton_2->setText(name[2]);
    ui->pushButton_3->setText(name[3]);
}

void SecDialog::saveUserInfo()
{
    QFile file("C:\\Users\\Kwon Geon\\Documents\\GitHub\\screenMirrorTest\\userInfo.txt");

    if( !file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }

    QTextStream in(&file);
    QString text =
}



void SecDialog::on_pushButton_clicked() // 이미 로그인 된 사람 클릭시
{
    login_select(1);
}
void SecDialog::on_pushButton_2_clicked()
{
     login_select(2);
}
void SecDialog::on_pushButton_3_clicked()
{
     login_select(3);
}


void SecDialog::login_select(int userNum)
{
    if(name[userNum] == "+")
        login_createAccount(userNum);
    else
        login_signIn(userNum);
}


// if user
void SecDialog::login_signIn(int userNum)
{
    n=new MainWindow(this,net);

    net=new NetConnection(this,"125.6.37.219",&SecDialog::loginComplete2);
    // net-> 한방에로그인( name[userNum] ) ;

}
void SecDialog::loginComplete2(int a)
{
    n->show();
    n->sampling();
}



// if new comer
void SecDialog::login_createAccount(int userNum)
{
    // set page2
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
    // set page2


    net=new NetConnection(this,"125.6.37.219",&SecDialog::loginComplete);

    QString m = QString::number(net->get_devicecode());
    ui->pwd->setAlignment(Qt::AlignCenter);
    ui->pwd->setText(m);

    n = new MainWindow(this,net);
}

void SecDialog::loginComplete(int a)
{
    // file modify


    n->show();
    n->sampling();
}



