#ifndef INITSCREEN_H
#define INITSCREEN_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class initscreen;
}

class initscreen : public QDialog
{
    Q_OBJECT

public:
    explicit initscreen(QWidget *parent = nullptr);
    ~initscreen();

private slots:
    void on_pushButton_clicked();

private:
    Ui::initscreen *ui;
    MainWindow *screen;
};

#endif // INITSCREEN_H
