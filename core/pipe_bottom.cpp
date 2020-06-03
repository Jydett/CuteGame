#include "pipe_bottom.h"
#include <QPainter>

PipeBottom::PipeBottom()
{
    this->textureData = QPixmap(":/assets/images/pipebottom.png");
    setRect(0, 0, 28, 16);
}

void PipeBottom::setPosition(int x, int y)
{
    setRect(x, y, 28, 16);
}

void PipeBottom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF pos = rect().topLeft();
    painter->drawPixmap(
        QPointF(pos.x(), pos.y()),
        textureData,
        QRectF(0, 0, 28, 16)
    );
}

