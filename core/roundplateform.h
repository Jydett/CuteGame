#ifndef ROUNDPLATEFORM_H
#define ROUNDPLATEFORM_H
#include "inert.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>

class RoundPlateform: public Inert, public QGraphicsPolygonItem
{
public:
    RoundPlateform(QPolygonF poly);
    void remove() override;
    void setPosition(int x, int y) override;
};

#endif // ROUNDPLATEFORM_H
