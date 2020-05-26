#ifndef PLAYER2_H
#define PLAYER2_H
#include "../core/keyboardcontrollable.h"
#include "../view/levelview.h"

class Player : public Entity
{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    Player(LevelView* view);
    void movementUpdated(qreal dX, qreal dY) override;
    void hit(GameObject* what, Direction fromDir) override;

protected:
//    bool onJump() override;//FIXME
    bool handleInput() override;
    void update() override;

private:
    QPixmap textureData;
    QGraphicsTextItem * debugIfo;
    LevelView * view;

    int spriteWidth;
    int spriteHeight;
    int annimationIndex;
    int lastDirection;

    bool isCrouching;
    bool downKeyPressedLastFrame;

    int annimationTimer;
};

#endif // PLAYER2_H
