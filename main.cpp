#include <QApplication>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QObject>

#include "scene/playscene.h"
#include "view/levelview.h"
#include "player/player.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //add a view
    QGraphicsView * view = new LevelView;
//    view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    PlayScene * scene = new PlayScene();
    view->setScene(scene);
    view->setSceneRect(0, 0, 100000000, 100000000);


    //create an vieable item
    Player * player = new Player(view);

    //add the item to the scene
    //make the player focusable -> mendatory to get key events
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    view->centerOn(0, 0);

    view->show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer.start(1000 / 60);

    return a.exec();
}
