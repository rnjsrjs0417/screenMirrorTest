#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QSpinBox;

class MainWindow : public QMainWindow
{
    bool mouseStat;                 //
    int mouseClickPoint, xDelta;    //

    int cursor_xPos, cursor_yPos;//Curor value

    //Initial Postion values of Widgets
    int cal_xPos, cal_yPos;
    int clock_xPos,clock_yPos;


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

private:
    //void configureSpinBox(QSpinBox *spinBox,int min,int max) const;
    void onMouseEvent(const QPoint &pos);
    Ui::MainWindow *ui;
    QTimer *timer;


};
#endif // MAINWINDOW_H
