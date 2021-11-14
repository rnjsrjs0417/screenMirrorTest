QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    initscreen.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    GBHealth.hpp \
    UltraFace.hpp \
    gb_thread.hpp \
    initscreen.h \
    lib_header.hpp \
    mainwindow.h

FORMS += \
    initscreen.ui \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    bl.png \
    heart.jpg \
    o2.jpg \
    pre.jpg \
    weather.png

INCLUDEPATH += C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\install\include

LIBS += \
        C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_calib3d430.dll \
        C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_core430.dll \
        C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_dnn430.dll \
        C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_features2d430.dll \
        C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_flann430.dll \
       C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_gapi430.dll \
        C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_highgui430.dll \
       C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_imgcodecs430.dll \
       C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_imgproc430.dll \
       C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_ml430.dll \
       C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_objdetect430.dll \
       C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_photo430.dll \
       C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_stitching430.dll \
       C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_video430.dll \
       C:\Users\kwang\Desktop\opencv-4.3.0\qtbuild\bin\libopencv_videoio430.dll



win32: LIBS += -L$$PWD/../../Desktop/opencv-4.3.0/qtbuild/lib/ -lgbface

INCLUDEPATH += $$PWD/../../Desktop/opencv-4.3.0/qtbuild/include
DEPENDPATH += $$PWD/../../Desktop/opencv-4.3.0/qtbuild/include

win32: LIBS += -L$$PWD/../../Desktop/opencv-4.3.0/qtbuild/lib/ -lgbhealth

INCLUDEPATH += $$PWD/../../Desktop/opencv-4.3.0/qtbuild/include
DEPENDPATH += $$PWD/../../Desktop/opencv-4.3.0/qtbuild/include
