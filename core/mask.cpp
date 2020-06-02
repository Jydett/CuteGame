#include "mask.h"
#include "../scene/playscene.h"

Mask::Mask()
{
    collidable = false;
    collected = false;
    setRect(0, 0, 16, 16);
    this->textureData = QPixmap(":/assets/images/mask.png");
}

void Mask::setPosition(int x, int y) {
    setRect(x, y, 16, 16);
}

void Mask::paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (PlayScene::showBoundingBoxes) {
        painter->drawRect(rect().toAlignedRect());
    } else {
        QPointF pos = rect().topLeft();
        painter->drawPixmap(
            QPointF(pos.x(), pos.y()),
            textureData,
            QRectF(0, 0, 16, 16)
        );
    }
}

void Mask::hit(GameObject *what, Direction fromDir)
{
    Player* player = dynamic_cast<Player*>(what);
    if (! collected && player != nullptr) {
        collected = true;
        player->isMasked = true;
        toRemove = true;
        return;
    }
}
