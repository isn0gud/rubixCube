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
    glwidget.cpp \
    cube.cpp \
    rubixcube.cpp \
    side.cpp \
    row.cpp

HEADERS  += glwidget.h \
    cube.h \
    rubixcube.h \
    side.h \
    row.h

RESOURCES += resources.qrc

OTHER_FILES += \
    vertexShader.vsh \
    fragmentShader.fsh \
    pickingFragShader.frag \
    pickingVertexShader.vsh
