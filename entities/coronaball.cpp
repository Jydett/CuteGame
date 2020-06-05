#include "coronaball.h"
#include "../scene/playscene.h"
#include <QPainter>

CoronaBall::CoronaBall() : Ennemy(":/assets/images/virus.png", 16, 16) {

}

void CoronaBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (PlayScene::showBoundingBoxes)
        painter->drawRect(rect().toAlignedRect());
    QPointF pos = boundingRect().topLeft();
    painter->drawPixmap(
        QPointF(pos.x(), pos.y()),
        textureData,
        QRectF(annimationIndex * width, 0, width, height)
    );
}
