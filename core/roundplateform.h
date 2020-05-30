#ifndef ROUNDPLATEFORM_H
#define ROUNDPLATEFORM_H
#include "inert.h"
#include <QGraphicsEllipseItem>

class RoundPlateform: public Inert, public QGraphicsEllipseItem
{
public:
    RoundPlateform();
    void remove() override;
    void setPosition(int x, int y) override;
};

#endif // ROUNDPLATEFORM_H
