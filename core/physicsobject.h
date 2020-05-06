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

private:
    QPointF collisionPoints[8];
    bool collide();

protected:
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

    void advance(int step) override;
    bool virtual handleInput() { return false; };

};

#endif // PHYSICSOBJECT_H
