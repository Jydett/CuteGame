#include "PhysicsObject.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QRectF>
#include <QPainterPath>
#include <QtMath>

PhysicsObject::PhysicsObject()
{
    qreal mScale = 60.0;
    accX = 0.2 * mScale;
    decX = 0.3 * mScale;
    maxSpeedX = 5.0 * mScale;
    maxSpeedY = 10.0 * mScale;

    speedX = 0;
    speedY = 0;

    jumpForce = 12.0 * mScale;
    accY = 0.5 * mScale;

    jumping = false;
    jumpRequested = false;
}

void PhysicsObject::setCollisionPoint(QPointF points[8]) {
    for (int i = 0; i < 8; i++)
        collisionPoints[i] = points[i];
}

void PhysicsObject::generateCollisionBox() {
    QRectF rect = this->rect();
    qreal width = rect.width();
    qreal widthQ = width / 4;
    qreal height = rect.height();
    qreal heightQ = height / 4;
    QPointF points[8] = {
        QPointF(widthQ, 0), QPointF(3 * widthQ, 0),
        QPointF(widthQ, height), QPointF(3 * widthQ, height),
        QPointF(0, heightQ), QPointF(0, 3 * heightQ),
        QPointF(width, heightQ), QPointF(width, 3 * heightQ),
    };
    setCollisionPoint(points);
}

//collision detection
void PhysicsObject::advance(int phase) {
    if (! phase)
        return;

    static const qreal frameTime = 1.0 / 60.0; //60fps

    qreal playerX = x();
    qreal playerY = y();

    QRectF playerBounds = this->rect();

    QPointF topLeft = playerBounds.topLeft();
    QPointF topRight = playerBounds.topRight();
    QPointF bottomLeft = playerBounds.bottomLeft();
    QPointF bottomRight = playerBounds.bottomRight();

   static const int MASK_SIZE = 10;

    //we get near object
    QList<QGraphicsItem *> boundObjects = scene()->items(
        QPolygonF()
                << mapToScene(-MASK_SIZE + bottomLeft.x(), MASK_SIZE + bottomLeft.y())
                << mapToScene(-MASK_SIZE + topLeft.x(), -MASK_SIZE + topLeft.y())
                << mapToScene(MASK_SIZE + topRight.x(), -MASK_SIZE + topRight.y())
                << mapToScene(MASK_SIZE + bottomRight.x(), MASK_SIZE + bottomRight.y()));


    bool contactX = true, contactYbottom = true, contactYtop = true;

    static const int iterations = 3;
    qreal fallFactor = 1.0;
    // Keep iterating the contact solver until the maximum number of iterations is reached
    // or no collisions are detected

    qreal nextMoveX = speedX * frameTime;
    qreal nextMoveY = speedY * frameTime;
    for (int iteration = 0; iteration < iterations && (contactX || contactYbottom || contactYtop); iteration++)
        {
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
                    if (dir == 0 && nextMoveY > 0) continue;
                    if (dir == 1 && nextMoveY < 0) continue;
                    if (dir == 2 && nextMoveX > 0) continue;
                    if (dir == 3 && nextMoveX < 0) continue;

                    // Our current position along the anticipated movement vector of the player this frame
                    projectedMoveX = projectedMoveY = 0;

                    // Calculate the length of the movement vector using Pythagoras
                    vectorLength = sqrt(nextMoveX * nextMoveX + nextMoveY * nextMoveY);
                    segments = 0;

                    // Advance along the vector until it intersects with some geometry
                    // or we reach the end
                    while (! boundObject->contains(QPointF(
                                 collisionPoints[dir * 2].x() + playerX + projectedMoveX,
                                 collisionPoints[dir * 2].y() + playerY + projectedMoveY
                                                 )) &&
                           ! boundObject->contains(QPointF(
                                 collisionPoints[dir * 2 + 1].x() + playerX + projectedMoveX,
                                 collisionPoints[dir * 2 + 1].y() + playerY + projectedMoveY
                                                 )) && segments < vectorLength)
                    {
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

                // ================================================================================
                // Discrete contact solver
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

                    //Speculative Contacts
                    projectedMoveX = projectedMoveY = 0;

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

                if (nextMoveY > originalMoveY && originalMoveY < 0) {
                    contactYtop = true;
                }

                if (nextMoveY < originalMoveY && originalMoveY > 0) {
                    contactYbottom = true;
                }

                if (abs(nextMoveX - originalMoveX) > 0.01f) {
                    contactX = true;
                }

                // The player can't continue jumping if we hit the side of something, must fall instead
                // Without this, a player hitting a wall during a jump will continue trying to travel
                // upwards
                if (contactX && contactYtop && speedY < 0) {
                    speedY = nextMoveY = 0;
                }
            }
//            qDebug() << "top " << contactYtop << " bottom " << contactYbottom << "side" << contactX;

            // If a contact has been detected, apply the re-calculated movement vector
            // and disable any further movement this frame (in either X or Y as appropriate)
            if (contactYbottom || contactYtop) {
                //prevent flickering
                playerY += static_cast<int>(nextMoveY);
                speedY = 0;

                if (contactYbottom)
                    jumping = false;
            }

            if (contactX) {
                if (speedX != 0 && speedY > 0) {
                    fallFactor = 0;
                }
                playerX += static_cast<int>(nextMoveX);
                speedX = 0;
            }
        }

        playerX += (speedX * frameTime);
        playerY += (speedY * frameTime);


        //Screen looping
        if (playerY > 720) {
            playerY = playerBounds.width() + 50;
        }
        if (playerX < -640) {
            playerX = 640;
        } else if (playerX > 640) {
            playerX = -640;
        }

        setPos(playerX, playerY);


//    qDebug() << "contactX " << contactX << "  contactYBottom " << contactYbottom << "  contactYTop " << contactYtop
//             << " x: " << playerX << " y: " << playerY << " dx: " << speedX << " dy: " << speedY;

    bool moveRequested = handleInput();

//    qDebug() << "2FFall " << (contactYbottom || contactYtop);
    speedY = speedY + (accY);
//    qDebug() << "2FFall " << speedY;
    //decelerate if no move is requested
    if (! moveRequested) {
        if (speedX < 0) speedX += decX;
        if (speedX > 0) speedX -= decX;

        if (speedX > 0 && speedX < decX) speedX = 0;
        if (speedX < 0 && speedX > -decX) speedX = 0;
    }

    //clamp speed values
    if (speedX > maxSpeedX) speedX = maxSpeedX;
    if (speedX < -maxSpeedX) speedX = -maxSpeedX;
    if (speedY < -maxSpeedY) speedY = -maxSpeedY;
    if (speedY > maxSpeedY) speedY = maxSpeedY;
}
