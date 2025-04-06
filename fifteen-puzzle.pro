QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aialgorithm.cpp \
    aiplayer.cpp \
    astaraialgorithm.cpp \
    greedyaialgorithm.cpp \
    homescreen.cpp \
    humanplayer.cpp \
    leaderboardscreen.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    playermanager.cpp \
    playermanagerscreen.cpp \
    puzzlemodel.cpp \
    puzzlescreen.cpp \
    randomaialgorithm.cpp \
    screenmanager.cpp \
    statshandler.cpp

HEADERS += \
    aialgorithm.h \
    aiplayer.h \
    astaraialgorithm.h \
    greedyaialgorithm.h \
    homescreen.h \
    humanplayer.h \
    leaderboardscreen.h \
    mainwindow.h \
    player.h \
    playermanager.h \
    playermanagerscreen.h \
    puzzlemodel.h \
    puzzlescreen.h \
    randomaialgorithm.h \
    screenmanager.h \
    statshandler.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
