#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>
#include <QMouseEvent>

#define X_DELTA_CRIT 300

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->xSpinBox->setReadOnly(true);
    //ui->ySpinBox->setReadOnly(true);

    //ui->xSpinBox->setValue(cursor().pos().x());
    //ui->ySpinBox->setValue(cursor().pos().y());

    //configureSpinBox(ui->xSpinBox, -INT_MAX, +INT_MAX);
    //configureSpinBox(ui->ySpinBox, -INT_MAX, +INT_MAX); // spin box setting

    cal_xPos = ui->widget_calendar->pos().x();
    cal_yPos = ui->widget_calendar->pos().y();

    clock_xPos = ui->label_date_time->pos().x();
    clock_yPos = ui->label_date_time->pos().y(); // SAVE init postions of widgets

    //ui->widget_calendar->move(-500,0); // [TEST] Can move calendar to over the boundary of window / and load by drag

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT (myfunction()));
    timer->start(1000); // countset by 1 sec

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::myfunction() // Operates in every 1 sec
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->label_date_time->setText(time_text);
}

//void MainWindow::configureSpinBox(QSpinBox *spinBox, int min, int max) const
//{
    //spinBox->setMinimum(min);
    //spinBox->setMaximum(max);
//}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
   onMouseEvent(event->pos());
   event->accept(); //QWidget::mouseDoubleClickEvent(event); equal.
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(this->mouseStat == true)
    {
        ui->label_date_time->move(cursor().pos().x()-mouseClickPoint,clock_yPos); //
        ui->widget_calendar->move(cursor().pos().x()-mouseClickPoint,cal_yPos);
    }


    onMouseEvent(event->pos());
    event->accept();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->mouseClickPoint = cursor().pos().x();   //
    this->mouseStat = true;                       // widget,screen slide

    onMouseEvent(event->pos());
    event->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    ui->widget_calendar->move(cal_xPos,cal_yPos);
    ui->label_date_time->move(clock_xPos,clock_yPos); // 일단은 제자리로 돌아오기

    onMouseEvent(event->pos());
    event->accept();
}

void MainWindow::onMouseEvent( const QPoint &pos)
{
    cursor_xPos = pos.x();
    cursor_yPos = pos.y();
    qDebug()<<"Xpos : "<<cursor_xPos<<"Ypos : "<<cursor_yPos;

    //ui->xSpinBox->setValue(pos.x());
    //ui->ySpinBox->setValue(pos.y());
}
