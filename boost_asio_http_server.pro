DESTDIR = bin

QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle


INCLUDEPATH += C:/boost_1_80_0
LIBS += -lws2_32
LIBS += -lwsock32

SOURCES += \
    main.cpp \
    server/Server.cpp \
    server/Session.cpp \
    server_processor/ServerProcessor.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    server/Server.h \
    server/Session.h \
    server_processor/IServerProcessor.h \
    server_processor/ServerProcessor.h \
    server_processor/testJsonBoost.h \
    server_processor/testJsonBoostQString.h \
    server_processor/testJsonQt.h
