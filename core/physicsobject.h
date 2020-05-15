#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include <QGraphicsItem>

#define GRAVITY 0.5
#define FRICTION 0.5

class PhysicsObject : public QGraphicsRectItem
{
public:

    PhysicsObject();
    void accelerate(qreal accelX, qreal accelY);
    void move(qreal xDelta, qreal yDelta);
    void setCollisionPoint(QPointF collisions[8]);
    void generateCollisionBox();

    //todo signal ??
    virtual void movementUpdated(qreal dX, qreal dY) {};

private:
    QPointF collisionPoints[8];

protected:
    qreal LinearMovement(qreal pps/*, int delta*/);

    bool traversable;

//    virtual void collide(PhysicsObject * other) = 0;

    //inherited posX, posY

    qreal accX, decX;

    qreal speedX, speedY;

    qreal maxSpeedX, maxSpeedY;

    qreal jumpForce;

    //gravity
    qreal accY;

    //true if currently jumping / prevents double jump
    bool jumping;

    bool jumpRequested;

    //collision flags
    bool contactX = true, contactYbottom = true, contactYtop = true;

    void advance(int step) override;
    bool virtual handleInput() { return false; };

};

#endif // PHYSICSOBJECT_H
