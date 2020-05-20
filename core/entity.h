#ifndef ENTITY_H
#define ENTITY_H
#include <QGraphicsRectItem>
#include "gameobject.h"
#include "Type.h"

class Entity : public GameObject, public QGraphicsRectItem
{
public:
    Entity();
    virtual bool handleInput() { return false; };
    enum { Type = ENTITY_TYPE };
    int type() const override { return Type; };

private:
    void accelerate(qreal accelX, qreal accelY);
    void move(qreal xDelta, qreal yDelta);
    void setCollisionPoint(QPointF collisions[8]);

    //todo signal ??
    virtual void movementUpdated(qreal dX, qreal dY) {};

protected:
    QPointF collisionPoints[8];
    bool dead;
    bool dying;

    //inherited posX, posY

    qreal accX, decX;

    qreal maxSpeedX, maxSpeedY;

    qreal jumpForce;

    qreal speedX, speedY;

    //gravity
    qreal accY;

    //true if currently jumping / prevents double jump
    bool jumping;

    bool jumpRequested;

    //collision flags
    bool contactX = true, contactYbottom = true, contactYtop = true;

    void advance(int step) override;
    void generateCollisionBox();
};

#endif // ENTITY_H
