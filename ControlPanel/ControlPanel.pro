QT += quick virtualkeyboard

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        src/CApp.cpp \
        src/CCommander.cpp \
        src/CUIModel.cpp

RESOURCES += qml.qrc

target_build {
    DEFINES += TARGET_BUILD

    INCLUDEPATH += inc/xenomai
    INCLUDEPATH += $$(SDKTARGETSYSROOT)/usr/include/evl/include
    HEADERS += inc/xenomai/Xeno4CommandInterface.h
    HEADERS += inc/xenomai/Xeno4Device.h

    SOURCES += src/xenomai/Xeno4CommandInterface.cpp
    SOURCES += src/xenomai/Xeno4Device.cpp

    LIBS += -levl -lpthread
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    inc/CApp.h \
    inc/CCommander.h \
    inc/CUIModel.h \
    inc/CommandInterface.h


INCLUDEPATH += inc/
