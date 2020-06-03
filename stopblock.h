#ifndef STOPBLOCK_H
#define STOPBLOCK_H
#include <QGraphicsRectItem>
#include "core/inert.h"
#include "core/Type.h"
#include <QGraphicsScene>


class StopBlock : public Inert, public QGraphicsRectItem
{
public:
    StopBlock();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setPosition(int x, int y) override;
    enum { Type = BLOCK_TYPE };
    int type() const override { return Type; };
    void remove() override {
        scene()->removeItem(this);
    }
};

#endif // STOPBLOCK_H
