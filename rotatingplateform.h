#ifndef ROTATINGPLATEFORM_H
#define ROTATINGPLATEFORM_H

#include <QGraphicsRectItem>


class RotatingPlateform : public QGraphicsRectItem
{
public:
    RotatingPlateform();
    void tick();

private:
    qreal angle;
    int timer;

protected:
    void advance(int step) override;
};

#endif // ROTATINGPLATEFORM_H
