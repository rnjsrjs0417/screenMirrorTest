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

    net=new NetConnection(this,"125.6.37.219",&SecDialog::loginComplete2);

    name[1] = "dsf"; name[2] = "sdf"; name[3] = "asdf";
    id[1] = ""; id[2] = ""; id[3] = "";
    // LOAD user info with txt file communication
    loadUserInfo();
    saveUserInfo();

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
    QFile file("C:\\Users\\kwang\\Documents\\screenMirrorTest\\userInfo.txt");

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


    //label set
    ui->pushButton->setText(name[1]);
    ui->pushButton_2->setText(name[2]);
    ui->pushButton_3->setText(name[3]);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_2->setText(id[1]);
    file.close();
}

void SecDialog::saveUserInfo()
{
    QFile file("C:\\Users\\kwang\\Documents\\screenMirrorTest\\userInfo.txt");

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
    n->show();
    n->sampling();
    //net=new NetConnection(this,"125.6.37.219",&SecDialog::loginComplete2);
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


    //net=new NetConnection(this,"125.6.37.219",&SecDialog::loginComplete);

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



