#include "ennemy.h"
#include "player.h"
#include "../core/inert.h"
#include "../scene/playscene.h"

Ennemy::Ennemy()
{
    qreal scale = 60.0;
    accX = 0.10 * scale * scale;
    maxSpeedX = 3.0 * scale;
    wallHit = 0;
    direction = 0;
    setRect(0, 0, 32, 32);
    generateCollisionBox();
    textureData = QPixmap(":/assets/images/virus.png");
}

void Ennemy::hit(GameObject* what, Direction fromDir) {
    if (fromDir == SIDE) {
        Inert* inert = dynamic_cast<Inert*>(what);
        if (inert != nullptr && inert->isCollidable()) {
            if (! jumpRequested) {
                wallHit++;
            }
        }
    }
    Player* player = dynamic_cast<Player*>(what);
    if (fromDir != TOP && player != nullptr) {
        qDebug() << "Ennemy touché";
        return;
    }
}

void Ennemy::setPosition(int x, int y) {
    setX(x); setY(y);
}

void Ennemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (PlayScene::showBoundingBoxes)
        painter->drawRect(rect().toAlignedRect());
    QPointF pos = boundingRect().topLeft();
    painter->drawPixmap(
        QPointF(pos.x(), pos.y()),
        textureData,
        QRectF(0, 0, 32, 32)
    );
}

bool Ennemy::handleInput()
{
    if (!jumping) {
        if (wallHit == 1) {
            jumping = true;
            jumpRequested = true;
            speedY = -jumpForce;
        } else if (wallHit > 1) {
            wallHit = 0;
            if (direction == 0) {
                direction = 1;
            } else {
                direction = 0;
            }
        }
    }
    if (direction == 0) {
        speedX -= linearMovement(accX);
    } else {
        speedX += linearMovement(accX);
    }
    return true;
}
