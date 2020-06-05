#ifndef REAPEATABLETEXTUREDITEM_H
#define REAPEATABLETEXTUREDITEM_H

#include "../core/inert.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>


class ReapeatableTexturedItem : public Inert, public QGraphicsRectItem
{
public:
    ReapeatableTexturedItem(QString file, int width, int height, int textureSize);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void nextFrame();
    void setPosition(int x, int y) override;
    void setWidth(int width);
    int width;
    void remove() override {
        scene()->removeItem(this);
    }
private:
    int maxFrame;
    int currentFrame;
    int height;
    int textureSize;
    QPixmap textureData;
};

#endif // REAPEATABLETEXTUREDITEM_H
