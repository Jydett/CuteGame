#include "playscene.h"
#include "../rotatingplateform.h"
#include "../antigravityfield.h"
#include "../core/reapeatabletextureditem.h"
#include "../surpriseblock.h"

PlayScene::PlayScene()
{

//    RotatingPlateform* rooo = new RotatingPlateform();
//    this->addItem(rooo);

//    QGraphicsRectItem * ground = new QGraphicsRectItem();
//    ground->setRect(0, 150, 500, 3);
//    ground->setTransformOriginPoint(ground->boundingRect().center());
//    ground->setRotation(340);
//    this->addItem(ground);


//    QGraphicsRectItem * mur = new QGraphicsRectItem();
//    mur->setRect(150, 300, 75, 200);
//    this->addItem(mur);

//    QGraphicsEllipseItem * mur2 = new QGraphicsEllipseItem();
//    mur2->setRect(-300, 400, 200, 200);
//    this->addItem(mur2);

//    QGraphicsEllipseItem * mur3 = new QGraphicsEllipseItem();
//    mur3->setRect(-30, 550, 300, 50);
//    this->addItem(mur3);


//    QGraphicsRectItem * ground1 = new QGraphicsRectItem();
//    ground1->setRect(0, 600, 3000, 20);
//    this->addItem(ground1);

    const int TEXTURE_SIZE = 16;

    ReapeatableTexturedItem * petit = new ReapeatableTexturedItem(":/assets/images/brick.png", 1, 1, TEXTURE_SIZE);
    petit->setPosition(230, 600 - 16);
    this->addItem(petit);

    ReapeatableTexturedItem * ground1 = new ReapeatableTexturedItem(":/assets/images/brick.png", 200, 1, TEXTURE_SIZE);
    ground1->setPosition(0, 600);
    this->addItem(ground1);

    ReapeatableTexturedItem * mur = new ReapeatableTexturedItem(":/assets/images/brick.png", 1, 3, TEXTURE_SIZE);
    mur->setPosition(260, 600 - 48);
    this->addItem(mur);

//    ReapeatableTexturedItem * mur2 = new ReapeatableTexturedItem(":/assets/images/brick.png", 1, 2, TEXTURE_SIZE);
//    mur2->setPosition(300, 600 - 32);
//    this->addItem(mur2);

//    QGraphicsRectItem * ladder = new AntigravityField();
//    ladder->setRect(550, 100, 100, 20);
//    this->addItem(ladder);

    for (auto i = 0; i < 20; i++) {
        SurpriseBlock * block = new SurpriseBlock(i % 2 == 0);
        block->setPosition(300 + (i * 32), 490);
        this->addItem(block);
    }

    for (auto i = 0; i < 19; i++) {
        SurpriseBlock * block = new SurpriseBlock(i % 2 == 1);
        block->setPosition(316 + (i * 32), 420);
        this->addItem(block);
    }



//    ReapeatableTexturedItem * myFirstBlock = new ReapeatableTexturedItem(":/assets/images/brick.png", 1, 1, TEXTURE_SIZE);
//    myFirstBlock->setPos(-400, 150);
//    this->addItem(myFirstBlock);

//    ReapeatableTexturedItem * mySecondBlock = new ReapeatableTexturedItem(":/assets/images/brick.png", 2, 2, TEXTURE_SIZE);
//    mySecondBlock->setPos(-200, 150);
//    this->addItem(mySecondBlock);


//    ReapeatableTexturedItem * myThirdBlock = new ReapeatableTexturedItem(":/assets/images/brick.png", 10, 2, TEXTURE_SIZE);
//    myThirdBlock->setPosition(200, 600 - TEXTURE_SIZE);
//    this->addItem(myThirdBlock);

//    ReapeatableTexturedItem * myFourthBlock = new ReapeatableTexturedItem(":/assets/images/brick.png", 1, 4, TEXTURE_SIZE);
//    myFourthBlock->setPosition(500, 600 - TEXTURE_SIZE * 4);
//    this->addItem(myFourthBlock);
}


