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
    blocks/pipe_bottom.cpp \
    blocks/pipe_top.cpp \
    blocks/reapeatabletextureditem.cpp \
    blocks/roundplateform.cpp \
    blocks/stopblock.cpp \
    blocks/surpriseblock.cpp \
    collectible/mask.cpp \
    collectible/soap_item.cpp \
    collectible/toiletpaper.cpp \
    core/entity.cpp \
    core/gameobject.cpp \
    core/inert.cpp \
    core/keyboardstatus.cpp \
    entities/coronaball.cpp \
    entities/ennemy.cpp \
    entities/player.cpp \
    entities/soap.cpp \
    entities/spit.cpp \
    entities/thug.cpp \
    main.cpp \
    scene/playscene.cpp \
    scene/ui/button.cpp \
    sound/music.cpp \
    sound/sound.cpp \
    view/gamemenu.cpp \
    view/levelmenu.cpp \
    view/levelview.cpp \
    view/mainview.cpp

HEADERS += \
    blocks/pipe_bottom.h \
    blocks/pipe_top.h \
    blocks/reapeatabletextureditem.h \
    blocks/roundplateform.h \
    blocks/stopblock.h \
    blocks/surpriseblock.h \
    collectible/mask.h \
    collectible/soap_item.h \
    collectible/toiletpaper.h \
    core/entity.h \
    core/gameobject.h \
    core/inert.h \
    core/keyboardstatus.h \
    entities/coronaball.h \
    entities/ennemy.h \
    entities/player.h \
    entities/soap.h \
    entities/spit.h \
    entities/thug.h \
    scene/playscene.h \
    scene/ui/button.h \
    sound/music.h \
    sound/sound.h \
    view/gamemenu.h \
    view/levelmenu.h \
    view/levelview.h \
    view/mainview.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    music/bestMusic.mp3 \
    sounds/gruntsound.wav \
    sounds/mask.mp3 \
    sounds/breakingBlock.wav \
    sounds/coin.wav \
    sounds/finishLvl.wav \
    sounds/jump.wav \
    sounds/pain.wav \
    sounds/plop.mp3

RESOURCES += \
    assets.qrc
