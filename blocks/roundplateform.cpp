#include "roundplateform.h"
#include <QGraphicsScene>

RoundPlateform::RoundPlateform(QPolygonF poly) : QGraphicsPolygonItem(poly)
{

}

void RoundPlateform::setPosition(int x, int y) {
    setX(x); setY(y);
}

void RoundPlateform::remove() {
    this->scene()->removeItem(this);
}

