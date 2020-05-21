#include "surpriseblock.h"
#include <QRectF>
#include <QPainter>
#include <QDebug>

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
//    painter->drawRect(boundingRect());
    if (hidden && ! broken) return;
    QPointF pos = boundingRect().topLeft();
    painter->drawPixmap(
        QPointF(pos.x(), pos.y()),
        textureData,
        QRectF(brokenOffset, 0, size, size)
    );
}

void SurpriseBlock::hit(GameObject *what, Direction fromDir) {
    if (fromDir == TOP) {
        qDebug() << "block hit";
    }
}

void SurpriseBlock::collide(Player *player) {
    if (broken == false) {
        if (hidden) {
            collidable = true;
        }
        qDebug() << "collide";
        this->brokenOffset = 16;
        this->broken = true;
        this->scene()->update(boundingRect());
    }
}
