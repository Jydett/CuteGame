#include "soap_item.h"
#include "../player/player.h"
#include <QPainter>
#include "../scene/playscene.h"

SoapItem::SoapItem() {
    collidable = false;
    collected = false;
    setRect(0, 0, 12, 16);
    this->textureData = QPixmap(":/assets/images/soap_item.png");
}

void SoapItem::setPosition(int x, int y) {
    setRect(x, y, 12, 16);
}

void SoapItem::paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPointF pos = rect().topLeft();
    painter->drawPixmap(
        QPointF(pos.x(), pos.y()),
        textureData,
        QRectF(0, 0, 12, 16)
    );
    if (PlayScene::showBoundingBoxes) {
        painter->drawRect(rect());
    }
}

void SoapItem::hit(GameObject *what, Direction fromDir) {
    Player* player = dynamic_cast<Player*>(what);
    if (! collected && player != nullptr) {
        player->collectSoap();
        collected = true;
        toRemove = true;
        return;
    }
}

