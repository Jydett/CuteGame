#include <QApplication>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QObject>

#include "scene/playscene.h"
#include "view/levelview.h"
#include "player/player.h"
#include "sound/sound.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    PlayScene * scene = new PlayScene;


    //create an vieable item
    Player * player = new Player;

    //add the item to the scene
    scene->addItem(player);


    //add a view
    QGraphicsView * view = new LevelView;
    view->setFixedSize(QSize(1280, 720));

    //make the player focusable -> mendatory to get key events
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    view->setScene(scene);

    view->show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer.start(1000 / 60);

    //play music
    Sound * sound = new Sound();
    sound->playMusic(25);

    return a.exec();
}
