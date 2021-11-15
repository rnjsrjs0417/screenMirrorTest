#ifndef LIARDETECTOR_H
#define LIARDETECTOR_H

#include <QWidget>

namespace Ui {
class liarDetector;
}

class liarDetector : public QWidget
{
    Q_OBJECT

public:
    explicit liarDetector(QWidget *parent = nullptr);
    ~liarDetector();

private slots:
    void on_pushButton_clicked();

private:
    Ui::liarDetector *ui;
};

#endif // LIARDETECTOR_H
