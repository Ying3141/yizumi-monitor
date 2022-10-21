#-------------------------------------------------
#
# Project created by QtCreator 2022-09-30T16:30:33
#
#-------------------------------------------------

QT       += core gui
QT       += opcua
QT       += sql
QT       += charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = yizumi
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    hs_connect_to_server.cpp \
    hs_analyse.cpp \
    hs_opcuaclient.cpp \
    hs_collect_setting.cpp \
    hs_node.cpp \
    hs_analyse_action.cpp \
    hs_database.cpp \
    hs_corelatecof.cpp \
    hs_corelatecoefmodel.cpp \
    hs_historydata.cpp \
    HsMainWindow.cpp \
    HsBasicInfo.cpp \
    HsMonitoring.cpp \
    HsAnalysis.cpp \
    HsHomePage.cpp


HEADERS += \
        mainwindow.h \
    hs_connect_to_server.h \
    hs_analyse.h \
    hs_opcuaclient.h \
    hs_collect_setting.h \
    hs_node.h \
    hs_analyse_action.h \
    hs_database.h \
    hs_corelatecof.h \
    hs_corelatecoefmodel.h \
    hs_historydata.h \
    HsMainWindow.h \
    HsUI.h \
    HsBasicInfo.h \
    HsMonitoring.h \
    HsAnalysis.h \
    HsHomePage.h


FORMS += \
        mainwindow.ui \
    hs_connect_to_server.ui \
    hs_opcuaclient.ui \
    hs_collect_setting.ui \
    hs_analyse_action.ui \
    hs_analyse.ui \
    hs_database.ui \
    hs_corelatecof.ui \
    hs_corelatecoefmodel.ui \
    hs_historydata.ui \
    HsMainWindow.ui \
    HsBasicInfo.ui \
    HsMonitoring.ui \
    HsAnalysis.ui \
    HsHomePage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    hsui.qrc
