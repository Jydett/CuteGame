#ifndef PIPE_BOTTOM_H
#define PIPE_BOTTOM_H

#include "../core/inert.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

class PipeBottom : public Inert, public QGraphicsRectItem
{
public:
    PipeBottom();
    enum { Type = BLOCK_TYPE };
    int type() const override { return Type; };
    void setPosition(int x, int y) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void remove() override {
        scene()->removeItem(this);
    }
private:
    int height;
    QPixmap textureData;
};

#endif // PIPE_BOTTOM_H
