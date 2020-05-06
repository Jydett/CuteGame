#include "playscene.h"
#include "../rotatingplateform.h"
#include "../antigravityfield.h"

PlayScene::PlayScene()
{

    RotatingPlateform* rooo = new RotatingPlateform();
    this->addItem(rooo);

    QGraphicsRectItem * ground = new QGraphicsRectItem();
    ground->setRect(0, 150, 500, 3);
//    ground->setTransformOriginPoint(ground->boundingRect().center());
//    ground->setRotation(340);
    this->addItem(ground);

    QGraphicsRectItem * mur = new QGraphicsRectItem();
    mur->setRect(150, 300, 75, 200);
    this->addItem(mur);

    QGraphicsEllipseItem * mur2 = new QGraphicsEllipseItem();
    mur2->setRect(-300, 400, 200, 200);
    this->addItem(mur2);

    QGraphicsEllipseItem * mur3 = new QGraphicsEllipseItem();
    mur3->setRect(-30, 550, 300, 50);
    this->addItem(mur3);


    QGraphicsRectItem * ground1 = new QGraphicsRectItem();
    ground1->setRect(-600, 600, 1000, 20);
    this->addItem(ground1);

    QGraphicsRectItem * ladder = new AntigravityField();
    ladder->setRect(550, 100, 100, 500);
    this->addItem(ladder);
}
