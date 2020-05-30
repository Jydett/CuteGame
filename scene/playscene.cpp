#include "playscene.h"
#include "../rotatingplateform.h"
#include "../antigravityfield.h"
#include "../core/reapeatabletextureditem.h"
#include "../surpriseblock.h"
#include "../core/soap_item.h"
#include "../core/mask.h"
#include "../player/ennemy.h"
#include "../core/spit.h"
#include "../core/roundplateform.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJSonDocument>

bool PlayScene::showBoundingBoxes = false;

PlayScene::PlayScene()
{

////    RotatingPlateform* rooo = new RotatingPlateform();
////    this->addItem(rooo);

////    QGraphicsRectItem * ground = new QGraphicsRectItem();
////    ground->setRect(0, 150, 500, 3);
////    ground->setTransformOriginPoint(ground->boundingRect().center());
////    ground->setRotation(340);
////    this->addItem(ground);


////    QGraphicsRectItem * mur = new QGraphicsRectItem();
////    mur->setRect(150, 300, 75, 200);
////    this->addItem(mur);

////    QGraphicsEllipseItem * mur2 = new QGraphicsEllipseItem();
////    mur2->setRect(-300, 400, 200, 200);
////    this->addItem(mur2);

////    QGraphicsEllipseItem * mur3 = new QGraphicsEllipseItem();
////    mur3->setRect(-30, 550, 300, 50);
////    this->addItem(mur3);


////    QGraphicsRectItem * ground1 = new QGraphicsRectItem();
////    ground1->setRect(0, 600, 3000, 20);
////    this->addItem(ground1);

//    const int TEXTURE_SIZE = 16;

////    ReapeatableTexturedItem * petit = new ReapeatableTexturedItem(":/assets/images/brick.png", 1, 1, TEXTURE_SIZE);
////    petit->setPosition(230, 600 - 16);
////    this->addItem(petit);

//    ReapeatableTexturedItem * wall = new ReapeatableTexturedItem(":/assets/images/brick.png", 1, 6, TEXTURE_SIZE);
//    wall->setPosition(0, 500 + 16);
//    this->addItem(wall);


//    ReapeatableTexturedItem * wall2 = new ReapeatableTexturedItem(":/assets/images/brick.png", 1, 6, TEXTURE_SIZE);
//    wall2->setPosition(600, 500 + 16);
//    this->addItem(wall2);

//    ReapeatableTexturedItem * ground1 = new ReapeatableTexturedItem(":/assets/images/brick.png", 200, 1, TEXTURE_SIZE);
//    ground1->setPosition(0, 600);
//    this->addItem(ground1);

//    ReapeatableTexturedItem * ground2 = new ReapeatableTexturedItem(":/assets/images/brick.png", 10, 1, TEXTURE_SIZE);
//    ground2->setPosition(0, 500);
//    this->addItem(ground2);

////    ReapeatableTexturedItem * mur = new ReapeatableTexturedItem(":/assets/images/brick.png", 1, 3, TEXTURE_SIZE);
////    mur->setPosition(260, 600 - 48);
////    this->addItem(mur);

//    Ennemy * ennemy = new Ennemy();
//    ennemy->setPosition(280, 600 - 100);
//    this->addItem(ennemy);

////    ReapeatableTexturedItem * mur2 = new ReapeatableTexturedItem(":/assets/images/brick.png", 1, 2, TEXTURE_SIZE);
////    mur2->setPosition(300, 600 - 32);
////    this->addItem(mur2);

////    QGraphicsRectItem * ladder = new AntigravityField();
////    ladder->setRect(550, 100, 100, 20);
////    this->addItem(ladder);

//    for (auto i = 0; i < 6; i++) {
////        SurpriseBlock * block = new SurpriseBlock(i % 2 == 1);
////        block->setPosition(300 + (i * 25), 600 - 32 - i * 2);
////        this->addItem(block);

//        if (i == 5) {
//            Mask * mask = new Mask();
//            mask->setPosition(300 + (i * 32), 600 - 16);
//            this->addItem(mask);
//        } else {
//            Coin * coin = new Coin();
//            coin->setPosition(300 + (i * 32), 600 - 16);
//            this->addItem(coin);
//        }

//    }

//    for (auto i = 0; i < 5; i++) {
//        SurpriseBlock * block = new SurpriseBlock(i % 2 == 1);
//        block->setPosition(316 + (i * 32), 500);
//        this->addItem(block);
//    }

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

    QFile levelFile(QStringLiteral("C:/Users/Trombonesolo/Documents/JeuTuto/level/niveau1.json"));
    if (! levelFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    } else {
        loadLevel(QJsonDocument(QJsonDocument::fromJson(levelFile.readAll())).object());
        levelFile.close();
    }

    setBackgroundBrush(QPixmap(":/assets/images/bg.png"));

    Spit * spit = new Spit(1);
    spit->setPosition(200, 200);
    this->addItem(spit);

//    QGraphicsEllipseItem * mur3 = new RoundPlateform();
//    mur3->setRect(100, 400, 300, 100);
//    this->addItem(mur3);

}

#define BRICK 1
#define SURPRISE 2
#define SURPRISE_MUSH 3
#define SURPRISE_MASK 4
#define SURPRISE_UKN 5
#define COIN 6
#define VIRUS 7
#define BRICK_COIN 27
#define SURPRISE_INVI 28
#define SURPRISE_MUSH_INVI 29
#define SURPRISE_MASK_INVI 30
#define SURPRISE_UKN_INVI 31


void PlayScene::loadLevel(const QJsonObject& level) {
    this->clear();
    int width = qRound(level["width"].toDouble());
    QJsonArray data = level["layers"][0]["data"].toArray();
    int lastLineIndex = -1;
    ReapeatableTexturedItem * lastBlock = nullptr;
    for (int i = 0; i < data.size(); ++i) {
        int lineIndex = i / width;

        auto x = (i % width) * 16;
        auto y = (lineIndex) * 16 + 144;
        int blockType = qRound(data.at(i).toDouble());
        if (blockType == BRICK) {
            QString texture = ":/assets/images/brick.png";
            if (lastBlock == nullptr || lastLineIndex != lineIndex) {
                ReapeatableTexturedItem * block = new ReapeatableTexturedItem(texture, 1, 1, 16);
                block->setPosition(x, y);
                this->addItem(block);
                lastBlock = block;
            } else {
                lastBlock->setWidth(lastBlock->width + 1);
            }
            lastLineIndex = lineIndex;
        } else {
            lastBlock = nullptr;
             if (blockType == SURPRISE || blockType == SURPRISE_INVI ||
                   blockType == SURPRISE_MUSH || blockType == SURPRISE_MUSH_INVI ||
                   blockType == SURPRISE_MASK || blockType == SURPRISE_MASK_INVI
                ) {
                 GameObject * toSpawn = nullptr;
                 if (blockType == SURPRISE_MASK || blockType == SURPRISE_MASK_INVI) {
                     toSpawn = new Mask();
                 }

                 SurpriseBlock * block = new SurpriseBlock(blockType >= SURPRISE_INVI, toSpawn);
                 block->setPosition(x, y);
                 this->addItem(block);
             } else if (blockType == COIN) {
                 SoapItem * coin = new SoapItem();
                 coin->setPosition(x, y);
                 this->addItem(coin);
             } else if (blockType == VIRUS) {
                 Ennemy * virus = new Ennemy();
                 virus->setPosition(x, y);
                 this->addItem(virus);
             }
        }
    }
}




