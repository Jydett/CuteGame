#ifndef ENNEMY_H
#define ENNEMY_H
#include "../core/entity.h"

class Ennemy : public Entity
{
public:
    Ennemy(QString texture, int width, int height);
    void hit(GameObject* what, Direction fromDir) override;
    void setPosition(int x, int y) override;
    void hurt(GameObject* byWhat) override;
    void updateLogic() override;

protected:
    bool handleInput() override;
    QPixmap textureData;
    int direction;
    int wallHit;
    int annimationTimer;
    int annimationIndex;
    int width;
    int height;
};

#endif // ENNEMY_H
