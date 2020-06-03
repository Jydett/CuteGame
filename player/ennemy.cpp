#include "ennemy.h"
#include "player.h"
#include "../core/inert.h"
#include "../scene/playscene.h"

#define SIZE 16

Ennemy::Ennemy(QString texture, int width, int height)
{
    this->width = width;
    this->height = height;
    wallHit = 0;
    direction = 1;
    setRect(0, 0, width, height);
    generateCollisionBox();
    textureData = QPixmap(texture);
    this->maxSpeedX = maxSpeedX / 3;
    this->annimationIndex = 0;
    this->annimationTimer = 0;
}

void Ennemy::hit(GameObject* what, Direction fromDir) {
    if (fromDir == SIDE) {
        if (what == nullptr) {
            speedX = 0;
            direction = -direction;
            return;
        }
        Inert* inert = dynamic_cast<Inert*>(what);
        if (inert != nullptr && inert->isCollidable()) {
            speedX = 0;
            direction = -direction;
            return;
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

bool Ennemy::handleInput() {
    speedX += linearMovement(accX * direction);
    return true;
}

void Ennemy::hurt(GameObject* byWhat) {
    Entity * byWhayEntity = dynamic_cast<Entity *>(byWhat);
    if (byWhayEntity != nullptr) {
        this->speedX = byWhayEntity->sx() / 3;
        this->speedY = byWhayEntity->sy() / 3;
    }
    this->dead = true;
    this->toRemove = true;
}
