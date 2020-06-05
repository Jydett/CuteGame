#include "playscene.h"
#include "../core/reapeatabletextureditem.h"
#include "../surpriseblock.h"
#include "../core/soap_item.h"
#include "../core/mask.h"
#include "../player/coronaball.h"
#include "../player/thug.h"
#include "../core/spit.h"
#include "../core/pipe_top.h"
#include "../core/pipe_bottom.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>
#include "../core/toiletpaper.h"
#include "../stopblock.h"
#include <QGraphicsView>
#include <QList>
#include "../core/roundplateform.h"

bool PlayScene::showBoundingBoxes = false;

PlayScene::PlayScene() {
    setBackgroundBrush(QPixmap(":/assets/images/bg.png"));

//    QGraphicsEllipseItem * mur3 = new RoundPlateform();
//    mur3->setRect(100, 410, 300, 100);
//    this->addItem(mur3);

    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &PlayScene::advanceTest);
    timer->start(1000 / 60);
}

void PlayScene::load(QString path) {
    QFile levelFile(path);
    if (! levelFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    } else {
        loadLevel(QJsonDocument(QJsonDocument::fromJson(levelFile.readAll())).object());
        levelFile.close();
    }
}

#define BRICK 1
#define SURPRISE 2
#define SURPRISE_MUSH 3
#define SURPRISE_MASK 4
#define SURPRISE_UKN 5
#define SOAP 35
#define VIRUS 7
#define BRICK_DARK 8
#define BRICK_COIN 27
#define SURPRISE_INVI 29
#define SURPRISE_MUSH_INVI 30
#define SURPRISE_MASK_INVI 31
#define SURPRISE_UKN_INVI 32
#define ROAD 33
#define THUG 12
#define STOP 39
#define TOILET_PAPER 40
#define PIPE_TOP 10
#define PIPE_BOTTOM_DIRT 37
#define PIPE_BOTTOM 64

void PlayScene::loadLevel(const QJsonObject& level) {
    this->clear();

    int width = qRound(level["width"].toDouble());
    QJsonArray data = level["layers"][0]["data"].toArray();
    int lastLineIndex = -1;
    ReapeatableTexturedItem * lastBlock = nullptr;
    int lastBlockType = -1;
    for (int i = 0; i < data.size(); ++i) {
        int lineIndex = i / width;

        auto x = (i % width) * 16;
        auto y = (lineIndex) * 16 + 144;
        int blockType = qRound(data.at(i).toDouble());
        if (blockType == TOILET_PAPER) {
            ToiletPaper * tp = new ToiletPaper();
            tp->setPosition(x, y);
            this->addItem(tp);
            connect(tp, SIGNAL(nextLevel()), this, SLOT(doNextLevel()));
        } else if (blockType == PIPE_BOTTOM || blockType == PIPE_BOTTOM_DIRT) {
            PipeBottom * pipe = new PipeBottom();
            pipe->setPosition(x + 2, y);
            this->addItem(pipe);
        } else if (blockType == PIPE_TOP) {
            PipeTop * pipe = new PipeTop();
            pipe->setPosition(x, y);
            this->addItem(pipe);
        } else if (blockType == BRICK || blockType == ROAD || blockType == BRICK_DARK) {
            QString texture;
            if (blockType == BRICK) {
                texture = ":/assets/images/brick.png";
            } else if (blockType == ROAD) {
                texture = ":/assets/images/road.png";
            } else if (blockType == BRICK_DARK) {
                texture = ":/assets/images/brick_dark.png";
            }

            if (blockType != lastBlockType || lastBlock == nullptr || lastLineIndex != lineIndex) {
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
                 } else {
                     toSpawn = new SoapItem();
                 }

                 SurpriseBlock * block = new SurpriseBlock(blockType >= SURPRISE_INVI, toSpawn);
                 block->setPosition(x, y);
                 this->addItem(block);
             } else if (blockType == STOP) {
                 StopBlock * block = new StopBlock();
                 block->setPosition(x, y);
                 this->addItem(block);
             } else if (blockType == SOAP) {
                 SoapItem * coin = new SoapItem();
                 coin->setPosition(x, y);
                 this->addItem(coin);
             } else if (blockType == VIRUS) {
                 CoronaBall * virus = new CoronaBall();
                 virus->setPosition(x, y);
                 this->addItem(virus);
             } else if (blockType == THUG) {
                 Thug * thug = new Thug();
                 thug->setPosition(x, y - 16);
                 this->addItem(thug);
             }
        }
        lastBlockType = blockType;
    }
}

void PlayScene::doNextLevel()
{
    displayed = false;
    stopFrame = true;
}

void PlayScene::display() {
    displayed = true;
}

void PlayScene::stop() {
    displayed = false;
}

void PlayScene::advanceTest() {
    if (displayed) {
        QGraphicsScene::advance();
    } else if (stopFrame) {
        for (auto v : views()) {
            v->close();
        }
        emit changeLevel();
        stopFrame = false;
    }
}



