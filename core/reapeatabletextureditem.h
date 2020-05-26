#ifndef REAPEATABLETEXTUREDITEM_H
#define REAPEATABLETEXTUREDITEM_H

#include "inert.h"
#include <QGraphicsRectItem>


class ReapeatableTexturedItem : public Inert, public QGraphicsRectItem
{
public:
    ReapeatableTexturedItem(QString file, int width, int height, int textureSize);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void nextFrame();
    enum { Type = BLOCK_TYPE };
    int type() const override { return Type; };
    void setPosition(int x, int y);
private:
    int maxFrame;
    int currentFrame;
    int width;
    int height;
    int textureSize;
    QPixmap textureData;
};

#endif // REAPEATABLETEXTUREDITEM_H
