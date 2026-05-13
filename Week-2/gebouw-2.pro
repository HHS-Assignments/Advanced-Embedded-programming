QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    codeslot.cpp \
    deur.cpp \
    draaideur.cpp \
    hallsensor.cpp \
    main.cpp \
    mainwindow.cpp \
    sleutelslot.cpp \
    schuifdeur.cpp \
    sensor.cpp

HEADERS += \
    codeslot.h \
    deur.h \
    deurdefs.h \
    draaideur.h \
    hallsensor.h \
    mainwindow.h \
    sleutelslot.h \
    schuifdeur.h \
    slot.h \
    sensor.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
   Gebouw.png
