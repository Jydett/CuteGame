#ifndef SPIT_H
#define SPIT_H
#include "../core/entity.h"


class Spit : public Entity
{
public:
    Spit(int direction);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void hit(GameObject* what, Direction fromDir) override;
    void setPosition(int x, int y) override;

protected:
    bool handleInput() override;
    void updateLogic() override;

private:
    QGraphicsTextItem * debugIfo;
    QPixmap textureData;
    int annimationTimer;
    int annimationIndex;
    int direction;
};

#endif // SPIT_H
