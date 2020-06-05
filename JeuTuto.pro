QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button.cpp \
    core/entity.cpp \
    core/gameobject.cpp \
    core/inert.cpp \
    core/keyboardstatus.cpp \
    core/mask.cpp \
    core/pipe_bottom.cpp \
    core/pipe_top.cpp \
    core/reapeatabletextureditem.cpp \
    core/soap.cpp \
    core/soap_item.cpp \
    core/spit.cpp \
    core/toiletpaper.cpp \
    main.cpp \
    player/coronaball.cpp \
    player/ennemy.cpp \
    player/player.cpp \
    player/thug.cpp \
    scene/gamemenu.cpp \
    scene/levelmenu.cpp \
    scene/playscene.cpp \
    sound/music.cpp \
    sound/sound.cpp \
    stopblock.cpp \
    surpriseblock.cpp \
    view/levelview.cpp \
    view/mainview.cpp

HEADERS += \
    button.h \
    core/Type.h \
    core/entity.h \
    core/gameobject.h \
    core/inert.h \
    core/keyboardstatus.h \
    core/mask.h \
    core/pipe_bottom.h \
    core/pipe_top.h \
    core/reapeatabletextureditem.h \
    core/soap.h \
    core/soap_item.h \
    core/spit.h \
    core/toiletpaper.h \
    player/coronaball.h \
    player/ennemy.h \
    player/player.h \
    player/thug.h \
    scene/gamemenu.h \
    scene/levelmenu.h \
    scene/playscene.h \
    sound/music.h \
    sound/sound.h \
    stopblock.h \
    surpriseblock.h \
    view/levelview.h \
    view/mainview.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    music/bestMusic.mp3 \
    sounds/mask.mp3 \
    sounds/breakingBlock.wav \
    sounds/coin.wav \
    sounds/finishLvl.wav \
    sounds/jump.wav

RESOURCES += \
    assets.qrc
