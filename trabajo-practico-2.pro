QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    comun.cpp \
    cronometro.cpp \
    estacion.cpp \
    horizontal.cpp \
    juego.cpp \
    main.cpp \
    mainwindow.cpp \
    multiple.cpp \
    tablero.cpp \
    vertical.cpp

HEADERS += \
    comun.h \
    cronometro.h \
    estacion.h \
    horizontal.h \
    juego.h \
    mainwindow.h \
    multiple.h \
    tablero.h \
    vertical.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recursos.qrc
