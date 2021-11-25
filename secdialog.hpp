#ifndef SECDIALOG_HPP
#define SECDIALOG_HPP
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT
    QString name[5], id[5];
    int isNewcome=0;
    int userNum=0;

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void loadUserInfo();
    void saveUserInfo();

    void login_select();
    void login_createAccount();
    void login_signIn();
    void loginComplete(int a);
    void loginComplete2(int a);



private:
    Ui::SecDialog *ui;
    MainWindow *n;
};

#endif // SECDIALOG_HPP
