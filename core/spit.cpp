#include "spit.h"
#include "inert.h"
#include <QPainter>
#include "player/player.h"

Spit::Spit(int direction)
{
    this->annimationTimer = 0;
    this->annimationIndex = 0;
    setRect(0, 0, 9, 9);
    generateCollisionBox();
    textureData = QPixmap(":/assets/images/crachat.png");
    jumpRequested = true;
    jumpForce = 300;
    this->direction = direction;
    this->debugIfo = new QGraphicsTextItem(this);
}

void Spit::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->drawPixmap(rect(), textureData, QRect(annimationIndex * 9, 0, 9, 9));
}

void Spit::updateLogic() {
    Entity::updateLogic();
    annimationTimer++;
    if (annimationTimer > 15) {
        annimationIndex = annimationIndex + 1;
        annimationIndex = annimationIndex % 4;
        annimationTimer = 0;
        update();
    }
}

void Spit::setPosition(int x, int y) {
    setX(x); setY(y);
}

bool Spit::handleInput() {
    speedX += linearMovement(accX * direction);
    if (wasOnGroundLastFrame && !jumping) {
        jumping = true;
        speedY = -jumpForce;
    }
    return true;
}

void Spit::hit(GameObject* what, Direction fromDir) {
    if (fromDir == SIDE) {
        if (what == nullptr) {
            this->dead = true;
            this->toRemove = true;
            return;
        }
        Inert* inert = dynamic_cast<Inert*>(what);
        if (inert != nullptr && inert->isCollidable()) {
            this->dead = true;
            this->toRemove = true;
        }
    }
    Player* player = dynamic_cast<Player*>(what);
    if (fromDir != TOP && player != nullptr) {
        player->hurt(this);
        this->dead = true;
        this->toRemove = true;
        return;
    }
}
