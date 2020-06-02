#include "ennemy.h"
#include "player.h"
#include "../core/inert.h"
#include "../scene/playscene.h"

#define SIZE 16

Ennemy::Ennemy()
{
    wallHit = 0;
    direction = 0;
    setRect(0, 0, SIZE, SIZE);
    generateCollisionBox();
    textureData = QPixmap(":/assets/images/virus.png");
    this->maxSpeedX = maxSpeedX / 3;
    this->annimationIndex = 0;
    this->annimationTimer = 0;
}

void Ennemy::hit(GameObject* what, Direction fromDir) {
    if (fromDir == SIDE) {
        Inert* inert = dynamic_cast<Inert*>(what);
        if (inert != nullptr && inert->isCollidable()) {
            if (direction == 1) {
                direction = 0;
            } else {
                direction = 1;
            }
        }
    }
    Player* player = dynamic_cast<Player*>(what);
    if (player != nullptr) {
        qDebug() << "Ennemy touché";
        return;
    }
}

void Ennemy::updateLogic() {
    if (dead) {
        toRemove = true;
    } else {
        Entity::updateLogic();
        annimationTimer++;
        if (annimationTimer > 6) {
            if (direction == 1) {
                annimationIndex = ((annimationIndex + 1) % 4);
            } else {
                annimationIndex = annimationIndex - 1;
                if (annimationIndex < 0) {
                    annimationIndex = 3;
                }
            }
            annimationTimer = 0;
        }
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
        QRectF(annimationIndex * SIZE, 0, SIZE, SIZE)
    );
}

bool Ennemy::handleInput()
{
    if (direction == 0) {
        speedX -= linearMovement(accX);
    } else {
        speedX += linearMovement(accX);
    }
    return true;
}

void Ennemy::hurt() {
    this->dead = true;
    this->toRemove = true;
}
