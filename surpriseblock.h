#ifndef SURPRISEBLOCK_H
#define SURPRISEBLOCK_H
#include <QGraphicsRectItem>
#include "core/inert.h"
#include "core/Type.h"
#include "player/player.h"

class SurpriseBlock : public Inert, public QGraphicsRectItem
{
public:
    SurpriseBlock(bool hidden);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setPosition(int x, int y);
    enum { Type = BLOCK_TYPE };
    int type() const override { return Type; };
    void hit(GameObject *what, Direction fromDir) override;

private:
    QPixmap textureData;
    int size;
    bool broken;
    bool deleteOnbreak;
    int brokenOffset;
    bool hidden;
};

#endif // SURPRISEBLOCK_H
