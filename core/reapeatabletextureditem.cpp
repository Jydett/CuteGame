#include "reapeatabletextureditem.h"

#include <QPainter>
#include <QDebug>
#include "../scene/playscene.h"
#include <QRectF>

ReapeatableTexturedItem::ReapeatableTexturedItem(QString file, int width, int height, int textureSize)
    : QGraphicsRectItem()
{
    this->width = width;
    this->height = height;
    this->textureSize = textureSize;
    this->textureData = QPixmap(file);
    //TODO gerer erreur
    maxFrame = textureData.width();
    this->currentFrame = 0;
}

void ReapeatableTexturedItem::setPosition(int x, int y) {
    setRect(x, y, textureSize * width, textureSize * height);
}

void ReapeatableTexturedItem::setWidth(int width) {
    this->width = width;
    QRectF rect = this->rect();
    setPosition(rect.x(), rect.y());
}

void ReapeatableTexturedItem::nextFrame() {
    currentFrame = currentFrame + textureSize;
    if (currentFrame >= maxFrame) {
        currentFrame = 0;
    }
}

void ReapeatableTexturedItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QPointF pos = rect().topLeft();

    if (PlayScene::showBoundingBoxes) {
        painter->drawRect(rect().toAlignedRect());
    } else {
        for (auto x = 0; x < width; x++) {
            for (auto y = 0; y < height; y++) {
    //            qDebug() << QPointF(x * textureSize + pos.x(), y * textureSize + pos.y()).x();
                painter->drawPixmap(
                    QPointF(x * textureSize + pos.x(), y * textureSize + pos.y()),
                    textureData,
                    QRectF(currentFrame, 0, textureSize, textureSize)
                );
            }
        }
    }
}
