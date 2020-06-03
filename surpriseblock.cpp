#include "surpriseblock.h"
#include <QRectF>
#include <QPainter>
#include <QDebug>
#include "scene/playscene.h"
#include "player/player.h"

SurpriseBlock::SurpriseBlock(bool hidden, GameObject* toSpawn)
{
    this->toSpawn = toSpawn;
    this->collidable = true;
    this->hidden = hidden;
    this->broken = false;
    if (hidden) collidable = false;
    this->brokenOffset = 0;
    this->size = 16;
    this->deleteOnbreak = true;
    setRect(0, 0, 16, 16);
    this->textureData = QPixmap(":/assets/images/surprise_block.png");
}

SurpriseBlock::~SurpriseBlock() {
    if (broken == false && toSpawn != nullptr) {
        delete toSpawn;
    }
}

void SurpriseBlock::setPosition(int x, int y) {
    setRect(x, y, 16, 16);
    if (toSpawn != nullptr) {
        toSpawn->setPosition(x, y - 16);
    }
}

void SurpriseBlock::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    if (PlayScene::showBoundingBoxes) {
        painter->drawRect(rect());
    } else {
        if (hidden && ! broken) return;
        QPointF pos = rect().topLeft();
        painter->drawPixmap(
            QPointF(pos.x(), pos.y()),
            textureData,
            QRectF(brokenOffset, 0, size, size)
        );
    }
}

void SurpriseBlock::hit(GameObject *what, Direction fromDir) {
    Player* player = dynamic_cast<Player*>(what);
    if (player != nullptr && fromDir == BOTTOM) {
        if (broken == false) {
            if (hidden) {
                collidable = true;
            }
            this->brokenOffset = 16;
            this->broken = true;
            if (toSpawn != nullptr) {
                this->scene()->addItem(dynamic_cast<QGraphicsItem *>(toSpawn));
            }
            this->scene()->update(boundingRect());
        }
    }
}
