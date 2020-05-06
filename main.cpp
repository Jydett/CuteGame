#include <QApplication>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QObject>

#include "scene/playscene.h"
#include "view/view.h"
#include "player/player.h"
#include "rotatingplateform.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    PlayScene * scene = new PlayScene;

    RotatingPlateform* rooo = new RotatingPlateform();
    scene->addItem(rooo);

    QGraphicsRectItem * ground = new QGraphicsRectItem();
    ground->setRect(0, 150, 500, 10);
    ground->setTransformOriginPoint(ground->boundingRect().center());
//    ground->setRotation(340);
    scene->addItem(ground);

    QGraphicsRectItem * mur = new QGraphicsRectItem();
    mur->setRect(150, 300, 75, 200);
    scene->addItem(mur);

    QGraphicsEllipseItem * mur2 = new QGraphicsEllipseItem();
    mur2->setRect(-300, 400, 200, 200);
    scene->addItem(mur2);

    QGraphicsEllipseItem * mur3 = new QGraphicsEllipseItem();
    mur3->setRect(-30, 550, 300, 50);
    scene->addItem(mur3);


    QGraphicsRectItem * ground1 = new QGraphicsRectItem();
    ground1->setRect(-600, 600, 1000, 20);
    scene->addItem(ground1);

    //create an vieable item
    Player * player = new Player();

    //add the item to the scene
    scene->addItem(player);


    //add a view
    QGraphicsView * view = new QGraphicsView();
    view->setFixedSize(QSize(1280, 720));
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    //make the player focusable -> mendatory to get key events
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    view->setScene(scene);

    view->show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer.start(1000 / 60);


    return a.exec();
}
