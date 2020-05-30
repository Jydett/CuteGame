#include "roundplateform.h"
#include <QGraphicsScene>

RoundPlateform::RoundPlateform()
{

}

void RoundPlateform::setPosition(int x, int y) {

}

void RoundPlateform::remove() {
    this->scene()->removeItem(this);
}

