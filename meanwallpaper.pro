TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        meanimage.cpp
INCLUDEPATH += \
        /usr/include/opencv4

unix|!macx: LIBS += -lopencv_core

unix:!macx: LIBS += -lopencv_video

unix:!macx: LIBS += -lopencv_highgui

unix:!macx: LIBS += -lopencv_videoio

unix:!macx: LIBS += -lopencv_imgproc

unix:!macx: LIBS += -lopencv_imgcodecs

HEADERS += \
    meanimage.h
