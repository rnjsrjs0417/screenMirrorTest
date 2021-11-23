<<<<<<< HEAD
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QMouseEvent>
#include <QWindow>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include<QPixmap>
#include <iomanip>
#include <iostream>
#include "winsock2.h"
#include <windows.h>

#include "UltraFace.hpp"
#include "GBHealth.hpp"
#include <opencv2/opencv.hpp>

#include "ui_mainwindow.h"



#define DELTA_X_CRIT 500
#define PAGE_WIDTH 1080
#define PAGE_HEIGHT 1920

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

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

    Q_OBJECT

public slots:
    void myfunction();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void sampling();
    void pixmapSet(Ui::MainWindow *ui);
    void dateSet(Ui::MainWindow *ui);
    void page2_button1();
    void test(int res);


private slots:
    void on_widget_calendar_clicked(const QDate &date);

    void on_cal_button_clicked();

    void on_page2_2button_clicked();

    void on_page2_3button_clicked();

    void on_pushButton_2_clicked();



private:
    Ui::MainWindow *ui;
    void onMouseEvent(const QPoint &pos);
    QTimer *timer;
};
#endif // MAINWINDOW_H












=======
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QMouseEvent>
#include <windows.h>
#include <QWindow>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include<QPixmap>
#include <iomanip>
#include <iostream>

#include "UltraFace.hpp"
#include "GBHealth.hpp"
#include <opencv2/opencv.hpp>

#include "ui_mainwindow.h"



#define DELTA_X_CRIT 500
#define PAGE_WIDTH 1080
#define PAGE_HEIGHT 1920

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

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

    Q_OBJECT

public slots:
    void myfunction();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void sampling();
    void pixmapSet(Ui::MainWindow *ui);
    void dateSet(Ui::MainWindow *ui);
    void page2_button1();


private slots:
    void on_widget_calendar_clicked(const QDate &date);

    void on_cal_button_clicked();

    void on_pushButton_clicked();

    void on_page2_2button_clicked();

    void on_page2_3button_clicked();



private:
    Ui::MainWindow *ui;
    void onMouseEvent(const QPoint &pos);
    QTimer *timer;
};
#endif // MAINWINDOW_H












>>>>>>> fbca8041db033b145428070811c624f39f4cb251
