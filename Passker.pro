CONFIG += c++17
CONFIG -= app_bundle
QT += core widgets gui
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
        main.cpp
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
        qrc.qrc
