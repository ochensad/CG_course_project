QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    drawer.cpp \
    light.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    normal.cpp \
    polygon.cpp \
    scene.cpp \
    surface.cpp \
    timer.cpp \
    zbuffer.cpp

HEADERS += \
    drawer.h \
    light.h \
    mainwindow.h \
    model.h \
    normal.h \
    polygon.h \
    scene.h \
    surface.h \
    timer.h \
    zbuffer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
