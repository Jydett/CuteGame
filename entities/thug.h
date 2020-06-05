#ifndef THUG_H
#define THUG_H

#include "ennemy.h"

class Thug : public Ennemy
{
public:
    Thug();
    void updateLogic() override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int spitTimer;
};

#endif // THUG_H
