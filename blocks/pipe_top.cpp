#include "pipe_top.h"
#include <QPainter>

PipeTop::PipeTop()
{
    this->textureData = QPixmap(":/assets/images/pipetop.png");
    setRect(0, 0, 32, 16);
}

void PipeTop::setPosition(int x, int y)
{
    setRect(x, y, 32, 16);
}

void PipeTop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF pos = rect().topLeft();
    painter->drawPixmap(
        QPointF(pos.x(), pos.y()),
        textureData,
        QRectF(0, 0, 32, 16)
    );
}
