#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDateTime>
#include <QMouseEvent>
#include <QGraphicsOpacityEffect>
#include "mainwindow.h"
#include <samplingthread.h>
#include <netconnection.h>

namespace Ui {
class SecDialog;
}

class DialogNet;

class SecDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SecDialog(QWidget *parent = nullptr, NetConnection* _net = nullptr);
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void sampling();
    void pixmapSet(Ui::SecDialog *ui);
    void dateSet(Ui::SecDialog *ui);
    void page2_button1();
    void test(int res);
    void get_string(std::string arr[]);

public slots:
    void myfunction();

private:
    NetConnection* net;

    bool mouseStat, page1_flag;
    int mouseClickPoint; // remeber only x point
    //Curor value
    int cursor_xPos, cursor_yPos;

    //Initial Postion values of Widgets
//    int clock_xPos,clock_yPos;
//    int cal_xPos, cal_yPos;
//    int date_xPos, date_yPos;

    //time values
    QString localTime;
    QString time_text;
    QTime time;
    QTimer *timer;
    Ui::SecDialog *ui;

public:
    int t=0;
    int r=0;
    int bpm=0, spo2=0;
    int minpress=0, maxpress=0;
    float temper=0;
    int bpm2=0,maxpress2=0;
    int bpm3=0,maxpress3=0;
    int errCheck=0;

    void onMouseEvent(const QPoint &pos);

private:
    void gotTodo(int res);
    void gotWeather(int res);

signals:

private:
    int sendHealthData(int pulse, int max, int min, int spo2);

private slots:
    void on_widget_calendar_clicked(const QDate &date);
    void on_cal_button_clicked();
    void on_page2_2button_clicked();
    void on_page2_3button_clicked();
    void on_pushButton_2_clicked();
    void on_radioButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_10_clicked();
};

#endif // SECDIALOG_H
