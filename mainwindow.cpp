#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   // ui->xSpinBox->setMinimum(-INT_MAX);
   // ui->xSpinBox->setMaximum(+INT_MAX);

    ui->xSpinBox->setReadOnly(true);
    ui->ySpinBox->setReadOnly(true);

    ui->xSpinBox->setValue(cursor().pos().x());
    ui->ySpinBox->setValue(cursor().pos().y());

    configureSpinBox(ui->xSpinBox, -INT_MAX, +INT_MAX);
    configureSpinBox(ui->ySpinBox, -INT_MAX, +INT_MAX);

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

void MainWindow::configureSpinBox(QSpinBox *spinBox, int min, int max) const
{
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    //ui->ESTADOLINEEDIT->setText("DoubleClick"); EST..인 라벨에 텍스트 부여하는 이벤트
    qDebug() << "doubleclick";
   onMouseEvent("DoubleClick",event->pos());
   event->accept();
    //QWidget::mouseDoubleClickEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "move";
    onMouseEvent("Move",event->pos());
    event->accept();
    //QWidget::mouseMoveEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
     qDebug() << "Press";
    onMouseEvent("Press",event->pos());
    event->accept();
    //QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
     qDebug() << "release";
    onMouseEvent("Release",event->pos());
    event->accept();
    //QWidget::mouseReleaseEvent(event);
}

void MainWindow::onMouseEvent(const QString &eventName, const QPoint &pos)
{
    ui->xSpinBox->setValue(pos.x());
    ui->ySpinBox->setValue(pos.y());
}
