#ifndef PLAYER2_H
#define PLAYER2_H

#include "../core/entity.h"
#include "../view/levelview.h"
#include "sound/sound.h"
#include <QGraphicsView>

class Player : public Entity
{
public:
    Player(LevelView* view);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void movementUpdated(qreal dX, qreal dY) override;
    void hit(GameObject* what, Direction fromDir) override;
    void setPosition(int x, int y) override;
    void hurt(GameObject* byWhat) override;
    bool isMasked;
    int life;
    void collectSoap();
    void collectMask();
    void collectToiletPaper();

protected:
    bool handleInput() override;
    void updateLogic() override;

private:
    QPixmap textureData;
    QGraphicsTextItem * debugIfo;
    LevelView * view;

    int spriteWidth;
    int spriteHeight;
    int lastDirection;

    bool isCrouching;
    bool downKeyPressedLastFrame;

    QGraphicsRectItem * soapBar;
    int soapCount;

    int annimationTimer;
    int annimationIndex;

    int xIndex, yIndex;

    int shootTimer;

    int invincibilityFrames;

    void shoot();
    void jump();

    Sound sound;
};

#endif // PLAYER2_H
