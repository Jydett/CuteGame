#include "surpriseblock.h"
#include <QRectF>
#include <QPainter>
#include <QDebug>

SurpriseBlock::SurpriseBlock()
{
    this->collidable = true;

    this->broken = false;
    this->brokenOffset = 0;
    this->size = 16;
    this->deleteOnbreak = true;
    this->textureData = QPixmap(":/assets/images/surprise_block.png");
}

void SurpriseBlock::setPosition(int x, int y) {
    setRect(x, y, size, size);
}

void SurpriseBlock::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
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
        this->brokenOffset = 16;
        this->broken = true;
    }
}
