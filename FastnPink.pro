TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        gra.cpp \
        gracz.cpp \
        main.cpp \
        pocisk.cpp \
        wrog.cpp
INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

DISTFILES += \
    images/background.jpg \
    images/ball.png \
    images/block01.png \
    images/block02.png \
    images/block03.png \
    images/block04.png \
    images/block05.png \
    images/paddle.png

HEADERS += \
    gra.h \
    gracz.h \
    pocisk.h \
    wrog.h
