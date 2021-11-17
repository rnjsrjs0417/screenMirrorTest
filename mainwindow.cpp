#include "mainwindow.h"
#include "ui_mainwindow.h"


int bpm=0, spo2=0;
int minpress=0, maxpress=0;
float temper=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    page1_flag = true;
    // init settings etc



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
//    if(SIGNAL(finished()))
//        qDebug() << "hola has gone";

    dateSet(ui);
    pixmapSet(ui);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunction() // Operates in every 1 sec
{
    time = QTime::currentTime();
    time_text = time.toString("AP hh : mm ");
    ui->label_date_time->setText(time_text);


    ui->label_2->setText(QString::number(bpm));
    ui->label_3->setText(QString::number(spo2));
    ui->label_5->setText(QString::number((minpress+maxpress)/2));

}

void MainWindow::onMouseEvent( const QPoint &pos) //
{
    cursor_xPos = pos.x();
    cursor_yPos = pos.y();
    //qDebug()<<"Xpos : "<<cursor_xPos<<"Ypos : "<<cursor_yPos;

    //ui->xSpinBox->setValue(pos.x());
    //ui->ySpinBox->setValue(pos.y());
}
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
    event->accept();}
void MainWindow::mousePressEvent(QMouseEvent *event)
{


    this->mouseClickPoint = cursor().pos().x();   //
    this->mouseStat = true;                       // widget,screen slide

    onMouseEvent(event->pos());
    event->accept();}
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

void MainWindow::sampling()
{
    // Your code.
       int vcNum = 0;
       const int CAM_WIDTH = 640;
       const int CAM_HEIGHT = 480;
       const int WAIT = 1;

       // GB code. You should have these.
       GBHealth gb;

       std::string face_detect_path = "C:\\Users\\Kwon Geon\\Desktop\\HELPME\\helpme\\model\\face_detection.onnx";
       std::string landmark_path = "C:\\Users\\Kwon Geon\\Desktop\\HELPME\\helpme\\model\\landmark_detection.onnx";

       int detect_interval = 8;            //얼굴인식 1초동안 실행 횟수
       float detect_threshold = 0.5;
       int detect_image_size = 200;

       UltraFace *ultra_face = new UltraFace(face_detect_path, detect_interval, detect_threshold, detect_image_size);
       #ifdef IS_LANDMARK
       ultra_face->LoadLandMark(landmark_path);
       #endif
       ultra_face->StartInterval();

       cv::VideoCapture cap_bgr, cap_ir;

       while(!cap_bgr.isOpened()){
           #ifdef _WIN32
           cap_bgr.open(vcNum++);
           #else
           cap_bgr.open(vcNum++, cv::CAP_V4L2);
           #endif
       }
       std::cout<< "Camera_" << vcNum-1 <<" Open"<<std::endl;


       std::cout << "Start grabbing" << std::endl;
       cap_bgr.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M','J','P','G'));
       cap_bgr.set(cv::CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
       cap_bgr.set(cv::CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);
       cap_bgr.set(cv::CAP_PROP_FPS, 30.0);


       // We generate separate thread timers to output Pulse and Blood Pressure Systolic values.
       // Because I just want to get values regularly.
       // You may get the value directly within the "while" below.

       int startTime = (cv::getTickCount()) / cv::getTickFrequency();

       GBThread *printBIO = new GBThread();
       printBIO->SetInterval([&]() {
           int nowTime = (cv::getTickCount()) / cv::getTickFrequency();
           std::cout<<cv::format("TIME: %.0fs", (double)(nowTime-startTime));

           // SAMPLE data to values
           if (gb.bpm_ > 0)
           {
               std::cout <<cv::format(", fps: %2.1f / BPM: %3d bpm", gb.fps_, gb.bpm_);
                // beat per minutes
                bpm = gb.bpm_;
               if(gb.spo2_ > 0)
               {
                   std::cout<<", Spo2: "<<gb.spo2_;
                   //o2
                   spo2=gb.spo2_;
               }

               if(gb.temperature_ > 0)
               {
                   std::cout<<", Temperature: "<<gb.temperature_;
                   //temperature
                   temper = gb.temperature_;

               }

               if (gb.blood_pressure_systolic_ > 0){
                   std::cout << ", blood pressure: " << gb.blood_pressure_diastolic_ <<" ~ "<< gb.blood_pressure_systolic_ << " mmHg";
                   switch (gb.condition_) {
                       case gb.CONDITION_WORST: std::cout << ", condition: worst"; break;
                       case gb.CONDITION_BAD: std::cout << ", condition: bad"; break;
                       case gb.CONDITION_LITTLE_BAD: std::cout << ", condition: little_bad"; break;
                       case gb.CONDITION_GOOD: std::cout << ", condition: good"; break;
                       default: break;

                       // blood pressure
                        minpress = gb.blood_pressure_diastolic_;
                        maxpress = gb.blood_pressure_systolic_;
                   }
               }
           }
           std::cout << std::endl;
       }, 1000);


       // Your code. Replace face and landmark find
       while (true)
       {
           cv::Mat mat_ir, mat_bgr;
           cap_bgr.read(mat_bgr);


           cv::flip(mat_bgr, mat_bgr, 1);


           if(ultra_face->IsInterval()){
               #ifdef IS_LANDMARK
               ultra_face->SetShareData(mat_bgr, ultra_face->DetectType::Landmark);
               #else
               ultra_face->SetShareData(mat_bgr, ultra_face->DetectType::Face);
               #endif
           }

           #ifdef IS_LANDMARK
               cv::Rect face;
               std::vector<cv::Point2f> params = ultra_face->Get_share_landmark_();
           #else
            cv::Rect2f face = ultra_face->Get_share_face_();
           #endif

           #ifdef IS_LANDMARK
               gb.CallErr(gb.Get(mat_bgr, params, face));
           #else
               gb.CallErr(gb.Get(mat_bgr, face));
           #endif

           cv::rectangle(mat_bgr, face, cv::Scalar(0, 255, 0), 1);
           cv::imshow("mat_bgr", mat_bgr);
           if (cv::waitKey(WAIT) > -1)
           {
               cv::destroyAllWindows();
               break;
           }
       }

       gb.StopInterval();

       ultra_face->Init();
       ultra_face->StopInterval();
       printBIO->StopInterval();

}

void MainWindow::pixmapSet(Ui::MainWindow *ui)
{
    QPixmap pix("C:\\Users\\Kwon Geon\\Documents\\GitHub\\screenMirrorTest\\weather.png");
    int w=ui->label_pic->width();
    int h=ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pix3("C:\\Users\\Kwon Geon\\Documents\\GitHub\\screenMirrorTest\\heart.jpg");
    ui->label_pulse->setPixmap(pix3.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pulse->setScaledContents(true);

    QPixmap pix4("C:\\Users\\Kwon Geon\\Documents\\GitHub\\screenMirrorTest\\pre.jpg");
    ui->label_pre->setPixmap(pix4.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pre->setScaledContents(true);

    QPixmap pix5("C:\\Users\\Kwon Geon\\Documents\\GitHub\\screenMirrorTest\\o2.jpg");
    ui->label_o2->setPixmap(pix5.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_o2->setScaledContents(true);


    QPixmap pix6("C:\\Users\\Kwon Geon\\Documents\\GitHub\\screenMirrorTest\\bl.png");
    ui->label_black->setPixmap(pix6.scaled(w,h,Qt::KeepAspectRatio));

    ui->label_s->setPixmap(pix6.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_black3->setPixmap(pix6.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_black3->setScaledContents(true);
}

void MainWindow::dateSet(Ui::MainWindow *ui)
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



void MainWindow::on_widget_calendar_clicked(const QDate &date)
{
    qDebug() << "DONT TOUCH ME FUCKin FREEK";
}

