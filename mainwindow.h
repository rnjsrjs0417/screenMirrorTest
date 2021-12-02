#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <secdialog.h>
#include <netconnection.h>

#define DELTA_X_CRIT 500
#define PAGE_WIDTH 1080
#define PAGE_HEIGHT 1920

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString name[5], id[5];
    int isNewcome;
    int userNum=0;
    Ui::MainWindow *ui;
    SecDialog *n;
    NetConnection *net;

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
};
#endif // MAINWINDOW_H
