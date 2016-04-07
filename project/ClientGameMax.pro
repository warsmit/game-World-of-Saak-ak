TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14

SOURCES += main.cpp \
    Game.cpp \
    Player.cpp \
    Entity.cpp \
    World.cpp \
    TextureManager.cpp \
    Animation.cpp \
    AnimationManager.cpp \
    Bullet.cpp \
    Meteor.cpp \
    FloatCircle.cpp \
    Stars.cpp

LIBS += -LC:/SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += C:/SFML/include
DEPENDPATH += C:/SFML/include

HEADERS += \
    Game.hpp \
    Player.hpp \
    Entity.hpp \
    World.hpp \
    TextureManager.hpp \
    Animation.hpp \
    AnimationManager.hpp \
    Bullet.hpp \
    Meteor.hpp \
    FloatCircle.hpp \
    Stars.hpp \
    Helper.hpp


