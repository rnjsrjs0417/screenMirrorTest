#include "secdialog.h"
#include "ui_secdialog.h"

using namespace std;

SecDialog::SecDialog(QWidget *parent, NetConnection* net) :
QDialog(parent),
ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    page1_flag = true;
    // init settings etc
    std::string arr[6];
    arr[0]="abc";
    this->net = net;

    net->get_todo(this, &SecDialog::gotTodo);
    net->get_weather(this, &SecDialog::gotWeather);
    ui->page1->move(0,0);
    ui->page2_1->move(0,0);
    ui->page2_2->move(0,1920);
    ui->page2_3->move(0,3940);
    ui->page2->move(1080,0);
    ui->label_23->setText("");

    setWindowFlags(Qt::FramelessWindowHint);
  //
    // Graphinc Settings
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

    get_string(arr);
    dateSet(ui);
    pixmapSet(ui);
    sampling();
}

void SecDialog::myfunction() // Operates in every 1 sec
{
    time = QTime::currentTime();
    time_text = time.toString("AP hh : mm ");
    ui->label_date_time->setText(time_text);

    if( errCheck != 0 || r==0){// -4 얼굴이중앙에안있을때 , -1 : 얼굴이 없을때

        ui->pushButton_2->setText("초기 정보 측정중");
        //qDebug()<<"카메라를 봐주세요";

       // qDebug()<<bpm2;
        //qDebug()<<bpm3;
        if(errCheck == 0)
        {
             ui->checking->setText("측정 중입니다, 움직이지 마세요");
             ui->page2_2button->setText("움직이지 마세요");
        }
        else
        {
             ui->checking->setText("얼굴을 찾을 수 없습니다");
             ui->page2_2button->setText("카메라를 봐주세요");
        }

    }
    else if(r==1){
        ui->pushButton_2->setText("시작하기");
        //qDebug()<<"거짓말 탐지중";

        ui->page2_2button->setText("결과보기");
        //qDebug()<<bpm2;
        //qDebug()<<bpm3;

        ui->checking->setText("");//생체 정보 측정 완료, 실시간 갱신중

        this->net->sendHealthData(bpm,maxpress,minpress,spo2);
        qDebug()<<"서버에업로드햇습니당" << bpm << maxpress << minpress << spo2;

}


//        if((bpm3-bpm2)<-2||(bpm3-bpm2)>2)
//            ui->page2_2button->setText("측정완료");

    ui->label_2->setText(QString::number(bpm));
    ui->label_3->setText(QString::number(spo2));
    ui->label_5->setText(QString::number(minpress));
    ui->label_20->setText(QString::number(maxpress));
}

void SecDialog::onMouseEvent( const QPoint &pos) //
{
    cursor_xPos = pos.x();
    cursor_yPos = pos.y();
    //qDebug()<<"Xpos : "<<cursor_xPos<<"Ypos : "<<cursor_yPos;

    //ui->xSpinBox->setValue(pos.x());
    //ui->ySpinBox->setValue(pos.y());
}

void SecDialog::mouseDoubleClickEvent(QMouseEvent *event)
{
   onMouseEvent(event->pos());
   event->accept(); //QWidget::mouseDoubleClickEvent(event); equal.
}

void SecDialog::mouseMoveEvent(QMouseEvent *event)
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
    event->accept();}
void SecDialog::mousePressEvent(QMouseEvent *event)
{


    this->mouseClickPoint = cursor().pos().x();   //
    this->mouseStat = true;                       // widget,screen slide

    onMouseEvent(event->pos());
    event->accept();
}

void SecDialog::mouseReleaseEvent(QMouseEvent *event)
{
// Move back to init pos  / when mouse released
//    ui->widget_calendar->move(cal_xPos,cal_yPos);
//    ui->label_date_time->move(clock_xPos,clock_yPos);
//    ui->label_date->move(date_xPos,date_yPos);

    //page_change function call : parameter -> cursor().pos().x() - mouseClickPoint
    int deltaX = cursor().pos().x() - mouseClickPoint;

    qDebug()<< deltaX;

    QPropertyAnimation *pa1 = new QPropertyAnimation(ui->page1,"geometry");
    QPropertyAnimation *pa2 = new QPropertyAnimation(ui->page2,"geometry");
    //ui->label_hello->setGraphicsEffect(efff);

    pa1->setEasingCurve(QEasingCurve::OutQuint);
    pa2->setEasingCurve(QEasingCurve::OutQuint);
    pa1->setDuration(200);
    pa2->setDuration(200);

   if(page1_flag == true)
   {
       if(deltaX < -DELTA_X_CRIT)
       {

           pa1->setStartValue(ui->page1->geometry());
           pa1->setEndValue(QRect(-PAGE_WIDTH,0,1080,1920));

           pa1->start();
           qDebug()<<ui->page1->pos().x();

           pa2->setStartValue(ui->page2->geometry());
           pa2->setEndValue(QRect(0,0,1080,1920));

           pa2->start();

            //ui->page1->move(-PAGE_WIDTH,0);
            //ui->page2->move(0,0);

            page1_flag = false;
            qDebug()<< "page1 -> page2 Accept";
            qDebug()<< " status :  " << page1_flag;
       }
       else
       {


           pa1->setStartValue(ui->page1->geometry());
           pa1->setEndValue(QRect(0,0,1080,1920));

           pa1->start();
           qDebug()<<ui->page1->pos().x();


           pa2->setStartValue(ui->page2->geometry());
           pa2->setEndValue(QRect(PAGE_WIDTH,0,1080,1920));

           pa2->start();


           //ui->page1->move(0,0);
           //ui->page2->move(PAGE_WIDTH,0);

           qDebug()<< "page1 -> page2 Deniied ! ";
           qDebug()<< " status :  " << page1_flag;
           //ui->widgets1->move(0,0);
       }
    }
   else
   {
       if(deltaX > DELTA_X_CRIT)
       {
           pa1->setStartValue(ui->page1->geometry());
           pa1->setEndValue(QRect(0,0,1080,1920));

           pa1->start();
           qDebug()<<ui->page1->pos().x();


           pa2->setStartValue(ui->page2->geometry());
           pa2->setEndValue(QRect(PAGE_WIDTH,0,1080,1920));

           pa2->start();


            //ui->page1->move(0,0);
            //ui->page2->move(PAGE_WIDTH,0);
            // ui->widgets1->move(0,0);
            page1_flag = true;
            qDebug()<< "page2 -> page1 Accept";
            qDebug()<< " status :  " << page1_flag;
       }
       else
       {
           pa1->setStartValue(ui->page1->geometry());
           pa1->setEndValue(QRect(-PAGE_WIDTH,0,1080,1920));
           pa1->start();
           qDebug()<<ui->page1->pos().x();

           pa2->setStartValue(ui->page2->geometry());
           pa2->setEndValue(QRect(0,0,1080,1920));
           pa2->start();

           //ui->page1->move(-PAGE_WIDTH,0);
           //ui->page2->move(0,0);
           qDebug()<< "page2 -> page1 Deniied ! ";
           qDebug()<< " status :  " << page1_flag;
           //ui->widgets1->move(-1080,0);
       }
   }


    onMouseEvent(event->pos());
    event->accept();
}

void SecDialog::sampling()
{
    SamplingThread* thread = new SamplingThread(this);
    thread->start();
}

void SecDialog::pixmapSet(Ui::SecDialog *ui)
{
    QPixmap pix("C:\\swproject\\screenMirrorTest\\weather.png");
    int w=ui->label_pic->width();
    int h=ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pix3("C:\\swproject\\screenMirrorTest\\heart.jpg");
    ui->label_pulse->setPixmap(pix3.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pulse->setScaledContents(true);

    QPixmap pix4("C:\\swproject\\screenMirrorTest\\pre.jpg");
    ui->label_pre->setPixmap(pix4.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pre->setScaledContents(true);

    QPixmap pix5("C:\\swproject\\screenMirrorTest\\o2.jpg");
    ui->label_o2->setPixmap(pix5.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_o2->setScaledContents(true);


    QPixmap pix6("C:\\swproject\\screenMirrorTest\\bl.png");
    ui->label_black->setPixmap(pix6.scaled(w,h,Qt::KeepAspectRatio));

    ui->label_s->setPixmap(pix6.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_black3->setPixmap(pix6.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_black3->setScaledContents(true);
}

void SecDialog::dateSet(Ui::SecDialog *ui)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT (myfunction()));
    timer->start(1000); // countset by 1 sec

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
}

void SecDialog::on_widget_calendar_clicked(const QDate &date)
{
    //qDebug() << "DONT TOUCH ME FUCKin FREEK";

    QPropertyAnimation *pa1 = new QPropertyAnimation(ui->widget_calendar,"geometry");
    pa1->setEasingCurve(QEasingCurve::OutQuint);
    pa1->setDuration(200);


    pa1->setStartValue(ui->widget_calendar->geometry());
    pa1->setEndValue(QRect(-400,590,380,270));
    pa1->start();

    //ui->widget_calendar->move(-400,590);
}

void SecDialog::on_cal_button_clicked()
{
    //qDebug() << "hello ~ ";
    // ui->widget_calendar->move(-20,590);

    QPropertyAnimation *pa1 = new QPropertyAnimation(ui->widget_calendar,"geometry");
    pa1->setEasingCurve(QEasingCurve::OutQuint);
    pa1->setDuration(200);


    pa1->setStartValue(ui->widget_calendar->geometry());
    pa1->setEndValue(QRect(-20,590,380,270));
    pa1->start();

}


void SecDialog::on_page2_2button_clicked() // 결과확인버튼
{
    if(r==0) return;

    bpm3=bpm;
    maxpress3=maxpress;

    // to page3
    ui->page2_1->move(0,-3840);

    //ui->page2_2->move(0,-1920);
    QPropertyAnimation *ppp1 = new QPropertyAnimation(ui->page2_2,"geometry");
    ppp1->setEasingCurve(QEasingCurve::OutQuint);
    ppp1->setDuration(200);

    ppp1->setStartValue(ui->page2_2->geometry());
    ppp1->setEndValue(QRect(0,-1920,1080,1920));
    ppp1->start();

    QPropertyAnimation *ppp = new QPropertyAnimation(ui->page2_3,"geometry");
    ppp->setEasingCurve(QEasingCurve::OutQuint);
    ppp->setDuration(200);

    ppp->setStartValue(ui->page2_3->geometry());
    ppp->setEndValue(QRect(0,0,1080,1920));
    ppp->start();




    ui->label_16->setText(QString::number(bpm2));
    ui->label_17->setText(QString::number(maxpress2));
    ui->label_18->setText(QString::number(bpm3));
    ui->label_19->setText(QString::number(maxpress3));


    if((bpm3+maxpress3)-(bpm2+maxpress2)<3)
    {
       ui->label_22->setText("진실!");
       ui->because->setText("옳은 말을 했군요 . . . ");
    }
    else
    {
       ui->label_22->setText("거짓!!!");
       ui->because->setText("당신은 거짓말을 하고 있습니다...");
    }
}

void SecDialog::on_page2_3button_clicked() //
{
    // to page1
    QPropertyAnimation *pppp = new QPropertyAnimation(ui->page2_1,"geometry");
    pppp->setEasingCurve(QEasingCurve::OutQuint);
    pppp->setDuration(200);


    pppp->setStartValue(ui->page2_1->geometry());
    pppp->setEndValue(QRect(0,0,1080,1920));
    pppp->start();


    ui->page2_2->move(0,1920);
    //ui->page2_3->move(0,3840);

    QPropertyAnimation *pppp1 = new QPropertyAnimation(ui->page2_3,"geometry");
    pppp1->setEasingCurve(QEasingCurve::OutQuint);
    pppp1->setDuration(200);

    pppp1->setStartValue(ui->page2_3->geometry());
    pppp1->setEndValue(QRect(0,3840,1080,1920));
    pppp1->start();


}

void SecDialog::page2_button1()
{
    if(r==0) return;

    bpm2=bpm;
    maxpress2=maxpress;
    for(int k=0;k<10000;k++)
        r=0;
    int n=0;
    qDebug()<< "startbutton clicked ";
    // ui->page2_1->move(0,-1920);

    QPropertyAnimation *pp1 = new QPropertyAnimation(ui->page2_1,"geometry");
    pp1->setEasingCurve(QEasingCurve::OutQuint);
    pp1->setDuration(200);

    pp1->setStartValue(ui->page2_1->geometry());
    pp1->setEndValue(QRect(0,-1920,1080,1920));
    pp1->start();

    // ui->page2_2->move(0,0);

    QPropertyAnimation *pp = new QPropertyAnimation(ui->page2_2,"geometry");
    pp->setEasingCurve(QEasingCurve::OutQuint);
    pp->setDuration(200);

    pp->setStartValue(ui->page2_2->geometry());
    pp->setEndValue(QRect(0,0,1080,1920));
    pp->start();

    ui->page2_3->move(0,1920);

    QGraphicsOpacityEffect *eefff = new QGraphicsOpacityEffect(this);
    ui->pushButton_10->setGraphicsEffect(eefff);
    QPropertyAnimation *aa1 = new QPropertyAnimation(eefff,"opacity");
    //ui->label_hello->setGraphicsEffect(efff);
    aa1->setDuration(15000);
    aa1->setStartValue(1);
    aa1->setEndValue(0);
    aa1->setEasingCurve(QEasingCurve::OutBack);
    aa1->start(QPropertyAnimation::DeleteWhenStopped);
    connect(aa1,SIGNAL(finished()),this,SLOT(hideThisWidget()));


//    QGraphicsOpacityEffect *efff = new QGraphicsOpacityEffect(this);
//    ui->page2_2button->setGraphicsEffect(efff);
//    QPropertyAnimation *aa = new QPropertyAnimation(efff,"opacity");



//    qDebug()<< "count start ";
//    aa->setDuration(8000);
//    aa->setStartValue(0);
//    aa->setEndValue(1);


//    aa->setEasingCurve(QEasingCurve::InExpo);
//    aa->start();
//    connect(aa,SIGNAL(finished()),this,SLOT(hideThisWidget));

//    if(SIGNAL(finished()))
//    {
//        qDebug()<< "signal called  ";
//        bb->setDuration(100);
//        bb->setStartValue(0);
//        bb->setEndValue(1);
//        bb->start();
//         qDebug()<< "bb start ";
//    }

    r=0;

}

void SecDialog::test(int res)
{
    ui->label_date->setText(" LOGIN COMPLETE ");
}

void SecDialog::on_pushButton_2_clicked()
{
     page2_button1();
}


void SecDialog::on_radioButton_clicked()
{
    QPropertyAnimation *pa1 = new QPropertyAnimation(ui->black,"geometry");
    pa1->setEasingCurve(QEasingCurve::OutQuint);
    pa1->setDuration(600);
    pa1->setStartValue(ui->black->geometry());
    pa1->setEndValue(QRect(0,0,1080,1920));
    pa1->start();
}


void SecDialog::on_pushButton_clicked()
{
    QPropertyAnimation *pa1 = new QPropertyAnimation(ui->black,"geometry");
    pa1->setEasingCurve(QEasingCurve::OutQuint);
    pa1->setDuration(600);
    pa1->setStartValue(ui->black->geometry());
    pa1->setEndValue(QRect(-1080,0,1080,1920));
    pa1->start();
}




void SecDialog::on_pushButton_3_clicked()
{
    QPropertyAnimation *pa1 = new QPropertyAnimation(ui->black,"geometry");
    pa1->setEasingCurve(QEasingCurve::OutQuint);
    pa1->setDuration(600);
    pa1->setStartValue(ui->black->geometry());
    pa1->setEndValue(QRect(0,0,1080,1920));
    pa1->start();
}

void SecDialog::get_string(std::string arr[])
{

    ui->pushButton_4->setText(QString::fromStdString(arr[0]));
    ui->pushButton_5->setText(QString::fromStdString(arr[0]));
    ui->pushButton_6->setText(QString::fromStdString(arr[0]));
    ui->pushButton_7->setText(QString::fromStdString(arr[0]));
    ui->pushButton_8->setText(QString::fromStdString(arr[0]));
    ui->pushButton_9->setText(QString::fromStdString(arr[0]));


}


void SecDialog::on_pushButton_10_clicked()
{
    on_page2_2button_clicked();
}

void SecDialog::gotTodo(int res){
    for(int i = 0; i < net->todo.size(); i++){
        qDebug() << net->todo[i].c_str();
    }
}

void SecDialog::gotWeather(int res){
    qDebug() << net->temp;
    qDebug() << net->humidity;
    qDebug() << net->rain;
}
