#ifndef CORONABALL_H
#define CORONABALL_H
#include "ennemy.h"

class CoronaBall : public Ennemy
{
public:
    CoronaBall();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // CORONABALL_H
