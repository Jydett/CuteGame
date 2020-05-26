#include "surpriseblock.h"
#include <QRectF>
#include <QPainter>
#include <QDebug>
#include "scene/playscene.h"

SurpriseBlock::SurpriseBlock(bool hidden)
{
    this->collidable = true;
    this->hidden = hidden;
    this->broken = false;
    if (hidden) collidable = false;
    this->brokenOffset = 0;
    this->size = 16;
    this->deleteOnbreak = true;
    this->textureData = QPixmap(":/assets/images/surprise_block.png");
}

void SurpriseBlock::setPosition(int x, int y) {
    setRect(x, y, size - 1, size - 1);
}

void SurpriseBlock::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {

    if (PlayScene::showBoundingBoxes)
        painter->drawRect(boundingRect());
    if (hidden && ! broken) return;
    QPointF pos = boundingRect().topLeft();
    painter->drawPixmap(
        QPointF(pos.x(), pos.y()),
        textureData,
        QRectF(brokenOffset, 0, size, size)
    );
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
            this->scene()->update(boundingRect());
        }
    }
}
