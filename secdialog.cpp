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

    userNum = 0 ;
    ui->page1->move(0,0);
    ui->page2->move(PAGE_WIDTH,0);

    setWindowFlags(Qt::FramelessWindowHint);

    net=new NetConnection(this,"125.6.37.219");

    name[1] = ""; name[2] = ""; name[3] = "";
    id[1] = ""; id[2] = ""; id[3] = "";
    // LOAD user info with txt file communication
    loadUserInfo();
    //saveUserInfo();

}

SecDialog::~SecDialog()
{
    delete ui;
}


void SecDialog::loadUserInfo()
{
    //file input
    QFile file("C:\\swproject\\screenMirrorTest\\userInfo.txt");

    if( !file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }

    QTextStream in(&file);

    name[1] = in.readLine();
    id[1] = in.readLine();
    name[2] = in.readLine();
    id[2] = in.readLine();
    name[3] = in.readLine();
    id[3] = in.readLine();

    if(name[1] == "") name[1] = "+";
    if(name[2] == "") name[2] = "+";
    if(name[3] == "") name[3] = "+";

    //label set

    ui->pushButton->setText(name[1]);
    ui->pushButton_2->setText(name[2]);
    ui->pushButton_3->setText(name[3]);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_2->setText(id[1]);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setText(id[2]);
    ui->label_4->setAlignment(Qt::AlignCenter);
    ui->label_4->setText(id[3]);
    file.close();
}

void SecDialog::saveUserInfo()
{
    QFile file("C:\\swproject\\screenMirrorTest\\userInfo.txt");

    if( !file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }

    QTextStream out(&file);

    out << name[1] << "\n";
    out << id[1] << "\n";
    out << name[2] << "\n";
    out << id[2] << "\n";
    out << name[3] << "\n";
    out << id[3] << "\n";

    file.flush();
    file.close();

}



void SecDialog::on_pushButton_clicked() // 이미 로그인 된 사람 클릭시
{   userNum = 1;
    login_select();

}
void SecDialog::on_pushButton_2_clicked()
{
     userNum = 2;
     login_select();

}
void SecDialog::on_pushButton_3_clicked()
{
     userNum = 3;
     login_select();
}


void SecDialog::login_select()
{

    if(name[userNum] == "+")
    {
        login_createAccount();
    }
    else
    {
        login_signIn();
    }
}


// if user
void SecDialog::login_signIn()
{
    net->load_user(name[userNum].toStdString(), &SecDialog::loginComplete2);
}
void SecDialog::loginComplete2(int a)
{
    if(isNewcome == 1)//file modify
    {
        name[userNum] = net->name.c_str();
        id[userNum] = net->id.c_str();
        saveUserInfo();
    }
    n=new MainWindow(this,net);
    n->show();
    n->sampling();

}



// if new comer
void SecDialog::login_createAccount()
{
    isNewcome = 1;

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

    QString m = QString::number(net->get_devicecode(&SecDialog::loginComplete2));
    ui->pwd->setAlignment(Qt::AlignCenter);
    ui->pwd->setText(m);
}

void SecDialog::loginComplete(int a)
{
    n->show();
    n->sampling();
}



