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


#define DELTA_X_CRIT 500
#define PAGE_WIDTH 1080
#define PAGE_HEIGHT 1920

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QSpinBox;

class MainWindow : public QMainWindow
{
    //mouse event values
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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


public slots:
    void myfunction();


private slots:
    void on_pushButton_clicked();

    void on_button_1_clicked();

private:
    //void configureSpinBox(QSpinBox *spinBox,int min,int max) const;
    void onMouseEvent(const QPoint &pos);
    void init_hiding();
    void page1_call();
    void page2_call();

    Ui::MainWindow *ui;
    QTimer *timer;


};
#endif // MAINWINDOW_H
