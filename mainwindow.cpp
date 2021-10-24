#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT (myfunction()));
    timer->start(1000); // 1초마다 타이밍을 재야됨 , 현재시간일단 띠용받아와서 그떄부터 잼
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunction()
{
    //qDebug() << "update..";
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->label_date_time->setText(time_text);
}

