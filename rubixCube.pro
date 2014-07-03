#-------------------------------------------------
#
# Project created by QtCreator 2014-07-03T14:22:21
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rubixCube
TEMPLATE = app


SOURCES += main.cpp\
    glwidget.cpp

HEADERS  += glwidget.h

RESOURCES += resources.qrc

OTHER_FILES += \
    vertexShader.vsh \
    fragmentShader.fsh
