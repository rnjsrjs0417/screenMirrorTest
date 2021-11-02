#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowFullScreen);

    // SAVE init postions of widgets
//    cal_xPos = ui->widget_calendar->pos().x();
//    cal_yPos = ui->widget_calendar->pos().y();
//    clock_xPos = ui->label_date_time->pos().x();
//    clock_yPos = ui->label_date_time->pos().y();
//    date_xPos = ui->label_date->pos().x();
//    date_yPos = ui->label_date->pos().y();


    //ui->widget_calendar->move(-500,0);
    // [TEST] Can move calendar to over the boundary of window / and load by drag



    // init settings etc
    page1_flag = true;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT (myfunction()));
    timer->start(1000); // countset by 1 sec

   /* QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    ui->label_hello->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
  //  ui->label_hello->setGraphicsEffect(eff);
    a->setDuration(7777);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
*/

    // now implement a slot called hideThisWidget() to do
    // things like hide any background dimmer, etc.

    QGraphicsOpacityEffect *efff = new QGraphicsOpacityEffect(this);
    ui->label_hello->setGraphicsEffect(efff);
    QPropertyAnimation *aa = new QPropertyAnimation(efff,"opacity");
    //ui->label_hello->setGraphicsEffect(efff);
    aa->setDuration(10000);
    aa->setStartValue(1);
    aa->setEndValue(0);
    aa->setEasingCurve(QEasingCurve::OutBack);
    aa->start(QPropertyAnimation::DeleteWhenStopped);
    connect(aa,SIGNAL(finished()),this,SLOT(hideThisWidget()));
    if(SIGNAL(finished()))
        qDebug() << "hola has gone";

    //date exp
    //localTime = QDateTime::currentDateTime().toString(Qt::TextDate);
    localTime = QDateTime::currentDateTime().toString("yyyy.MM.dd  ddd");
    ui->label_date->setText(localTime);
    QFont font = ui->label_date->font();
    font.setPointSize(30);
    ui->label_date->setFont(font);


    time = QTime::currentTime();
    time_text = time.toString("AP hh : mm ");
    ui->label_date_time->setText(time_text);
    QFont font2 = ui->label_date_time->font();
    font2.setPointSize(65);
    ui->label_date_time->setFont(font2);




    QPixmap pix("C:/Users/Kwon Geon/Documents/GitHub/screenMirrorTest/weather.png");
    int w=ui->label_pic->width();
    int h=ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pix3("C:/Users/Kwon Geon/Documents/GitHub/screenMirrorTest/heart.jpg");
    ui->label_pulse->setPixmap(pix3.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pulse->setScaledContents(true);

    QPixmap pix4("C:/Users/Kwon Geon/Documents/GitHub/screenMirrorTest/pre.jpg");
    ui->label_pre->setPixmap(pix4.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pre->setScaledContents(true);

    QPixmap pix5("C:/Users/Kwon Geon/Documents/GitHub/screenMirrorTest/o2.jpg");
    ui->label_o2->setPixmap(pix5.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_o2->setScaledContents(true);


    QPixmap pix6("C:/Users/Kwon Geon/Documents/GitHub/screenMirrorTest/bl.png");
    ui->label_black->setPixmap(pix6.scaled(w,h,Qt::KeepAspectRatio));

    ui->label_s->setPixmap(pix6.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_black3->setPixmap(pix6.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_black3->setScaledContents(true);


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

void MainWindow::page1_call()
{

}

void MainWindow::page2_call()
{

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
        if(page1_flag == true)
        {
            //ui->widgets1->move(cursor().pos().x()-mouseClickPoint,0);
            ui->page1->move(cursor().pos().x()-mouseClickPoint,0);
            ui->page2->move(PAGE_WIDTH+cursor().pos().x()-mouseClickPoint,0);
        }

        else if(page1_flag == false)
        {
            //ui->widgets1->move(cursor().pos().x()-mouseClickPoint-1080,0);
            ui->page1->move(cursor().pos().x()-mouseClickPoint-PAGE_WIDTH,0);
            ui->page2->move(cursor().pos().x()-mouseClickPoint,0);
        }

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

    //page_change function call : parameter -> cursor().pos().x() - mouseClickPoint
    int deltaX = cursor().pos().x() - mouseClickPoint;

    qDebug()<< deltaX;

   if(page1_flag == true)
   {
       if(deltaX < -DELTA_X_CRIT)
       {
            ui->page1->move(-PAGE_WIDTH,0);
            ui->page2->move(0,0);

            //ui->widgets1->move(-1080,0);
            page1_flag = false;
            qDebug()<< "page1 -> page2 Accept";
            qDebug()<< " status :  " << page1_flag;
       }
       else
       {
           ui->page1->move(0,0);
           ui->page2->move(PAGE_WIDTH,0);

           qDebug()<< "page1 -> page2 Deniied ! ";
           qDebug()<< " status :  " << page1_flag;
           //ui->widgets1->move(0,0);
       }
    }
   else
   {
       if(deltaX > DELTA_X_CRIT)
       {
            ui->page1->move(0,0);
            ui->page2->move(PAGE_WIDTH,0);
            // ui->widgets1->move(0,0);
            page1_flag = true;
            qDebug()<< "page2 -> page1 Accept";
            qDebug()<< " status :  " << page1_flag;
       }
       else
       {
           ui->page1->move(-PAGE_WIDTH,0);
           ui->page2->move(0,0);
           qDebug()<< "page2 -> page1 Deniied ! ";
           qDebug()<< " status :  " << page1_flag;
           //ui->widgets1->move(-1080,0);
       }
   }


    onMouseEvent(event->pos());
    event->accept();
}

void MainWindow::onMouseEvent( const QPoint &pos)
{
    cursor_xPos = pos.x();
    cursor_yPos = pos.y();
    //qDebug()<<"Xpos : "<<cursor_xPos<<"Ypos : "<<cursor_yPos;

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

