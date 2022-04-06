QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BaseUpdater.cpp \
    main.cpp \
    widget.cpp

OBJECTIVE_SOURCES += \
    CocoaInitializer.mm \
    SparkleUpdater.mm

HEADERS += \
    CocoaInitializer.h \
    BaseUpdater.h \
    NonCopyable.h \
    Singleton.h \
    SparkleUpdater.h \
    widget.h

FORMS += \
    widget.ui

LIBS += -framework AppKit
LIBS += -framework Carbon
LIBS += -framework Foundation
LIBS += -framework ApplicationServices
LIBS += -framework Sparkle

QMAKE_MAC_SDK = macosx10.13
QMAKE_INFO_PLIST = Info.1.5.0.plist

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
