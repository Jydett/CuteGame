#ifndef ENNEMY_H
#define ENNEMY_H
#include "../core/entity.h"

class Ennemy : public Entity
{
public:
    Ennemy();
    void hit(GameObject* what, Direction fromDir) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setPosition(int x, int y);

protected:
    bool handleInput() override;

private:
    QPixmap textureData;
    int direction;
    int wallHit;
};

#endif // ENNEMY_H
