#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QMouseEvent>
#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QSpinBox;

class MainWindow : public QMainWindow
{
    //mouse event values
    bool mouseStat;
    int mouseClickPoint, xDelta;

    //Curor value
    int cursor_xPos, cursor_yPos;

    //Initial Postion values of Widgets
    int clock_xPos,clock_yPos;
    int cal_xPos, cal_yPos;
    int date_xPos, date_yPos;

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
    void init_hiding();

private:
    //void configureSpinBox(QSpinBox *spinBox,int min,int max) const;
    void onMouseEvent(const QPoint &pos);

    Ui::MainWindow *ui;
    QTimer *timer;


};
#endif // MAINWINDOW_H
