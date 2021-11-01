#include "mainwindow.h"
#include "ui_mainwindow.h"


#define X_DELTA_CRIT 300

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // SAVE init postions of widgets
    cal_xPos = ui->widget_calendar->pos().x();
    cal_yPos = ui->widget_calendar->pos().y();
    clock_xPos = ui->label_date_time->pos().x();
    clock_yPos = ui->label_date_time->pos().y();
    date_xPos = ui->label_date->pos().x();
    date_yPos = ui->label_date->pos().y();


    //ui->widget_calendar->move(-500,0);
    // [TEST] Can move calendar to over the boundary of window / and load by drag



    // init settings etc

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT (myfunction()));
    timer->start(1000); // countset by 1 sec




    //date exp
    //localTime = QDateTime::currentDateTime().toString(Qt::TextDate);
    localTime = QDateTime::currentDateTime().toString("yyyy.MM.dd  ddd");
    ui->label_date->setText(localTime);

    time = QTime::currentTime();
    time_text = time.toString("AP hh : mm ");
    ui->label_date_time->setText(time_text);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_hiding()
{
    QObject().thread()->usleep(1000*1000*5);
    qDebug() << " 5 sec delayed ";
}

void MainWindow::myfunction() // Operates in every 1 sec
{
    time = QTime::currentTime();
    time_text = time.toString("AP hh : mm ");
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
    if(this->mouseStat == true) // move widgets with mouse events
    {
        ui->page1->move(cursor().pos().x()-mouseClickPoint,0);
        //ui->label_date_time->move(clock_xPos + cursor().pos().x()-mouseClickPoint,clock_yPos); //
        //ui->widget_calendar->move(cal_xPos + cursor().pos().x()-mouseClickPoint,cal_yPos);
        //ui->label_date->move(date_xPos + cursor().pos().x()-mouseClickPoint,date_yPos);
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
    // Move back to init pos  / when mouse released
//    ui->widget_calendar->move(cal_xPos,cal_yPos);
//    ui->label_date_time->move(clock_xPos,clock_yPos);
//    ui->label_date->move(date_xPos,date_yPos);
    ui->centralwidget->move(0,0);

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

// spin box settings( in initializer )

//ui->xSpinBox->setReadOnly(true);
//ui->ySpinBox->setReadOnly(true);

//ui->xSpinBox->setValue(cursor().pos().x());
//ui->ySpinBox->setValue(cursor().pos().y());

//configureSpinBox(ui->xSpinBox, -INT_MAX, +INT_MAX);
//configureSpinBox(ui->ySpinBox, -INT_MAX, +INT_MAX); // spin box setting

