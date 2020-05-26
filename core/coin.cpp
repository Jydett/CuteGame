#include "coin.h"
#include "../player/player.h"
#include <QPainter>

Coin::Coin()
{
    collidable = false;
    collected = false;
    setRect(0, 0, 12, 16);
    this->textureData = QPixmap(":/assets/images/coin.png");
}

void Coin::setPosition(int x, int y) {
    setRect(x, y, 12 - 1, 16 - 1);
}

void Coin::paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->drawRect(rect().toAlignedRect());
    QPointF pos = boundingRect().topLeft();
    painter->drawPixmap(
        QPointF(pos.x(), pos.y()),
        textureData,
        QRectF(0, 0, 12, 16)
    );
}

void Coin::hit(GameObject *what, Direction fromDir)
{
    Player* player = dynamic_cast<Player*>(what);
    if (! collected && player != nullptr) {
        qDebug() << "Argent ramassé";
        collected = true;
        scene()->removeItem(this);
        //FIXME fuite mémoire
//        delete this;
        return;
    }
}

