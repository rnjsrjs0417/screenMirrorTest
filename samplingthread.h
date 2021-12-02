#ifndef SAMPLINGTHREAD_H
#define SAMPLINGTHREAD_H

#include <QThread>
#include <secdialog.h>
#include "UltraFace.hpp"
#include "GBHealth.hpp"
#include <opencv2/opencv.hpp>

class SecDialog;

class SamplingThread : public QThread
{
public:
    SecDialog* window;
public:
    SamplingThread(SecDialog* w);
    void run() override;
};

#endif // SAMPLINGTHREAD_H
