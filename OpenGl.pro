#-------------------------------------------------
#
# Project created by QtCreator 2014-07-27T11:16:22
#
#-------------------------------------------------

QT       += core gui opengl serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glview.cpp \
    lightwindow.cpp \
    materialwindow.cpp \
    transformationswindow.cpp \
    serialwindow.cpp

HEADERS  += mainwindow.h \
    glview.h \
    lightwindow.h \
    materialwindow.h \
    defines.h \
    transformationswindow.h \
    serialwindow.h

FORMS    += mainwindow.ui \
    lightwindow.ui \
    materialwindow.ui \
    transformationswindow.ui \
    serialwindow.ui

LIBS += -lglut
