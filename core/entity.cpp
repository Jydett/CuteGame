#include "entity.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QRectF>
#include <QtMath>
#include "gameobject.h"

#include "../surpriseblock.h"

Entity::Entity()
{
    this->collidable = false;
    this->dying = false;
    this->dead = false;
    this->wasOnGroundLastFrame = false;

    qreal mScale = 60.0; //desired framerate
    accX = 0.2 * mScale * mScale;
    decX = 0.5 * mScale * mScale;
    accY = 0.4 * mScale * mScale;

    maxSpeedX = 5.0 * mScale;
    maxSpeedY = 8.0 * mScale;

    jumpForce = 10.0 * mScale;

    speedX = 0;
    speedY = 0;

    jumping = false;
    jumpRequested = false;
}

void Entity::setCollisionPoint(QPointF points[8]) {
    for (int i = 0; i < 8; i++)
        collisionPoints[i] = points[i];
}

void Entity::generateCollisionBox() {
    QRectF rect = this->rect();
    qreal width = rect.width();
    qreal widthQ = width / 4;
    qreal height = rect.height();
    qreal heightQ = height / 4;
    QPointF points[8] = {
        QPointF(widthQ, 1), QPointF(3 * widthQ, 1),
        QPointF(widthQ, height - 1), QPointF(3 * widthQ, height - 1),
        QPointF(1, heightQ), QPointF(1, 3 * heightQ),
        QPointF(width - 1, heightQ), QPointF(width - 1, 3 * heightQ),
    };
    setCollisionPoint(points);
}

//collision detection
void Entity::update() {

    static const int MASK_SIZE = 10;

    QPointF pos = this->pos();

    qreal playerX = x();
    qreal playerY = y();

    QRectF playerBounds = this->rect();

    QPointF topLeft = playerBounds.topLeft();
    QPointF topRight = playerBounds.topRight();
    QPointF bottomLeft = playerBounds.bottomLeft();
    QPointF bottomRight = playerBounds.bottomRight();

    qreal realAccY = accY;

    //we get near object
    QList<QGraphicsItem *> boundObjects = scene()->items(
        QPolygonF()
            << mapToScene(-MASK_SIZE + bottomLeft.x(), MASK_SIZE + bottomLeft.y())
            << mapToScene(-MASK_SIZE + topLeft.x(), -MASK_SIZE + topLeft.y())
            << mapToScene(MASK_SIZE + topRight.x(), -MASK_SIZE + topRight.y())
            << mapToScene(MASK_SIZE + bottomRight.x(), MASK_SIZE + bottomRight.y()));

//    qDebug() << "objects found: " << boundObjects.size();

    bool contactX = true, contactYbottom = true, contactYtop = true;
    static const int iterations = 3;
    qreal fallFactor = 1.0;
    // Keep iterating the contact solver until the maximum number of iterations is reached
    // or no collisions are detected

    for (int iteration = 0; iteration < iterations && (contactX || contactYbottom || contactYtop); iteration++) {

        qreal nextMoveX = linearMovement(speedX);
        qreal nextMoveY = linearMovement(speedY);

        contactX = contactYbottom = contactYtop = false;

        qreal projectedMoveX, projectedMoveY, originalMoveX, originalMoveY;

        originalMoveX = nextMoveX;
        originalMoveY = nextMoveY;

        float vectorLength;
        int segments;

        for (int o = 0; o < boundObjects.size() && !contactX && !contactYbottom && !contactYtop; o++)
        {
            QGraphicsItem * boundObject = boundObjects.at(o);
            if (boundObject == this) {
                continue;
            }
            int type = boundObject->type();
            if (type == 8) {//ignore text elem
                continue;
            }

            //antigravity
            bool isLadder = type == (UserType + 1);
            if (isLadder) {
                realAccY = - 2 * accY;
                continue;
            }

            GameObject * gameObject = nullptr;
            bool nonCollidableHit = false;
            bool notCollidable = false;
            if (type > (UserType + 10)) {
                gameObject = dynamic_cast<GameObject*>(boundObject);
                notCollidable = (gameObject->isCollidable() == false);
            }

            // ================================================================================
            // Speculative contacts section
            //
            // We will traverse along the movement vector of the player from his/her current
            // position until the final position for the frame to check if any geometry lies
            // in the way. If so, the vector is adjusted to end at the geometry's intersection
            // with the player's movement vector. This solves the so-called 'bullet through
            // paper' problem.
            // ================================================================================

            // We will test the four possible directions of player movement individually
            // dir: 0 = top, 1 = bottom, 2 = left, 3 = right
            for (int dir = 0; dir < 4; dir++) {
                if (dir == 0 && nextMoveY >= 0) continue; else
                if (dir == 1 && nextMoveY <= 0) continue; else
                if (dir == 2 && nextMoveX >= 0) continue; else
                if (dir == 3 && nextMoveX <= 0) continue;

                // Our current position along the anticipated movement vector of the player this frame
                projectedMoveX = projectedMoveY = 0;

                // Calculate the length of the movement vector using Pythagoras
                vectorLength = sqrt(nextMoveX * nextMoveX + nextMoveY * nextMoveY);
                segments = 0;

                // Advance along the vector until it intersects with some geometry
                // or we reach the end
                while (objectIsNotInCollisionPoints(boundObject, dir, projectedMoveX, projectedMoveY)
                       && segments < vectorLength) {
                    projectedMoveX += nextMoveX / vectorLength;
                    projectedMoveY += nextMoveY / vectorLength;
                    segments++;
                }

                // If an intersection occurred...
                if (segments < vectorLength) {
                    // Apply correction for over-movement
                    if (segments > 0) {
                        projectedMoveX -= nextMoveX / vectorLength;
                        projectedMoveY -= nextMoveY / vectorLength;
                    }

                    // Adjust the X or Y component of the vector depending on
                    // which direction we are currently testing
                    if (dir >= 2 && dir <= 3) nextMoveX = projectedMoveX;
                    if (dir >= 0 && dir <= 1) nextMoveY = projectedMoveY;
                }
            }

            //We skip the penetration resolution calculation if we hit an non collidable
            if (notCollidable == false) {
                // ================================================================================
                // Penetration resolution
                //
                // Here we look for existing collisions and nudge the player in the opposite
                // direction until the collision is solved. The purpose of iteration is because
                // the correction may cause collisions with other pieces of geometry. Iteration
                // also solves the so-called 'jitter' problem where a collision between the
                // player and the geometry is constantly solved and then re-introduced as the
                // player's position is nudged backwards and forwards between the same two points
                // repeatedly, creating jitter in the player's movement.
                // ================================================================================

                // We will test the four possible directions of player movement individually
                // dir: 0 = top, 1 = bottom, 2 = left, 3 = right
                for (int dir = 0; dir < 4; dir++) {
                    // Skip the test if the expected direction of movement makes the test irrelevant
                    // For example, we only want to test the top of the player's head when movement is
                    // upwards, not downwards. This is really important! If we don't do this, we can
                    // make corrections in the wrong direction, causing the player to magically jump
                    // up to platforms or stick to ceilings.
                    if (dir == 0 && nextMoveY > 0) continue;
                    if (dir == 1 && nextMoveY < 0) continue;
                    if (dir == 2 && nextMoveX > 0) continue;
                    if (dir == 3 && nextMoveX < 0) continue;

                    projectedMoveX = (dir >= 2 ? nextMoveX : 0);
                    projectedMoveY = (dir <  2 ? nextMoveY : 0);
                    while (boundObject->contains(QPointF(
                                 collisionPoints[dir * 2].x() + playerX + projectedMoveX,
                                 collisionPoints[dir * 2].y() + playerY + projectedMoveY
                                                 )) ||
                           boundObject->contains(QPointF(
                                 collisionPoints[dir * 2 + 1].x() + playerX + projectedMoveX,
                                 collisionPoints[dir * 2 + 1].y() + playerY + projectedMoveY
                                                 )))
                    {
                        if (dir == 0) {
                            projectedMoveY++;
                        } else if (dir == 1) {
                            projectedMoveY--;
                        } else if (dir == 2) {
                            projectedMoveX++;
                        } else if (dir == 3) {
                            projectedMoveX--;
                        }
                    }
                    if (dir >= 2 && dir <= 3) nextMoveX = projectedMoveX;
                    if (dir >= 0 && dir <= 1) nextMoveY = projectedMoveY;
                }
            }

            if (nextMoveY > originalMoveY && originalMoveY < 0) {
                contactYtop = true;
                if (gameObject != nullptr) this->hit(gameObject, TOP);
            }

            if (nextMoveY < originalMoveY && originalMoveY > 0) {
                contactYbottom = true;
                if (gameObject != nullptr) this->hit(gameObject, BOTTOM);
            }

            if (qFabs(nextMoveX - originalMoveX) > 0.01f) {
                contactX = true;
                if (gameObject != nullptr) this->hit(gameObject, SIDE);
            }

            //we cancel the collision flags if the collision was a walkable entity
            //but we still need to call the hit method
            if (notCollidable) {
                //we cancele the collision
                nextMoveY = originalMoveY;
                nextMoveX = originalMoveX;
                //when notCollidable is set: gameObject != nullptr
                if (contactX) contactX = false;
                if (contactYtop) contactYtop = false;
                if (contactYbottom) contactYbottom = false;
            }

            // The player can't continue jumping if we hit the side of something, must fall instead
            // Without this, a player hitting a wall during a jump will continue trying to travel
            // upwards
            if (contactX && contactYtop && speedY < 0) {
                speedY = nextMoveY = 0;
            }
        }

        // If a contact has been detected, apply the re-calculated movement vector
        // and disable any further movement this frame (in either X or Y as appropriate)
        if (contactYbottom || contactYtop) {
            //prevent flickering
            playerY += static_cast<int>(nextMoveY);
            speedY = 0;
            if (contactYbottom) jumping = false;
        }

        if (contactX) {
            if (speedX != 0 && speedY > 0) {
                fallFactor = 0;
            }
            playerX += static_cast<int>(nextMoveX);
            speedX = 0;
        }
    }


    //FIXME un peu dégeu ca non ? xD @Jydet
    if (speedY == 0) {
        wasOnGroundLastFrame = true;
    } else {
        wasOnGroundLastFrame = false;
    }

    qreal dX = linearMovement(speedX);
    qreal dY = linearMovement(speedY);
    if (dX != 0 || dY != 0) {
        playerX += dX;
        playerY += dY;
        movementUpdated(dX, dY);
    }

    if (playerX < 0) {
        playerX = 0;
    }

    setPos(playerX, playerY);
    bool moveRequested = handleInput();

    speedY = speedY + linearMovement(realAccY);

    //decelerate if no move is requested
    if (! moveRequested) {
        if (speedX < 0) speedX += linearMovement(decX);
        if (speedX > 0) speedX -= linearMovement(decX);

        // Deceleration may produce a speed that is greater than zero but
        // smaller than the smallest unit of deceleration. These lines ensure
        // that the player does not keep travelling at slow speed forever after
        // decelerating.
        if (speedX > 0 && speedX < linearMovement(decX)) speedX = 0;
        if (speedX < 0 && speedX > linearMovement(-decX)) speedX = 0;
    }

    //clamp speed values
    if (speedX > maxSpeedX) speedX = maxSpeedX;
    if (speedX < -maxSpeedX) speedX = -maxSpeedX;
    if (speedY < -maxSpeedY) speedY = -maxSpeedY;
    if (speedY > maxSpeedY) speedY = maxSpeedY;
}

bool Entity::objectIsNotInCollisionPoints(QGraphicsItem * boundObject, int dir, qreal projectedMoveX, qreal projectedMoveY) {
    qreal playerX = x();
    qreal playerY = y();
    return ! boundObject->contains(QPointF(
               collisionPoints[dir * 2].x() + playerX + projectedMoveX,
               collisionPoints[dir * 2].y() + playerY + projectedMoveY
                               )) &&
         ! boundObject->contains(QPointF(
               collisionPoints[dir * 2 + 1].x() + playerX + projectedMoveX,
               collisionPoints[dir * 2 + 1].y() + playerY + projectedMoveY
                               ));
}
