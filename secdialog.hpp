#ifndef SECDIALOG_HPP
#define SECDIALOG_HPP
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void loginComplete(int a);

private:
    Ui::SecDialog *ui;
    MainWindow *n;
};

#endif // SECDIALOG_HPP
