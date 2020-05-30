#ifndef ENTITY_H
#define ENTITY_H
#include <QGraphicsScene>
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
    virtual void hurt() {};

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

    bool wasOnGroundLastFrame;

    //collision flags
    bool contactX = true, contactYbottom = true, contactYtop = true;

    inline void advance(int step) override {
        if (! step) {
            updateLogic();
            GameObject::updateLogic();
        }
    };

    void remove() override {
        scene()->removeItem(this);
    }

    virtual void updateLogic() override;
    void generateCollisionBox();

    //FIXME inline ?
    bool objectIsNotInCollisionPoints(QGraphicsItem * boundObject, int dir, qreal projectedMoveX, qreal projectedMoveY);
};

#endif // ENTITY_H
