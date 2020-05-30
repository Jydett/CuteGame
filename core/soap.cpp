#include "soap.h"
#include "inert.h"
#include <QPainter>
#include "player/player.h"
#include "../player/ennemy.h"

Soap::Soap(bool direction)
{
    this->annimationTimer = 0;
    this->annimationIndex = 0;
    setRect(0, 0, 9, 9);
    generateCollisionBox();
    this->textureData = QPixmap(":/assets/images/soap.png");
    this->accY = 15;
    this->direction = direction ? 1 : -1;
    this->debugIfo = new QGraphicsTextItem(this);
    this->maxSpeedX = this->maxSpeedX * 1.1;
    this->speedX = this->direction * maxSpeedX;
}

void Soap::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->drawPixmap(rect(), textureData, QRect(annimationIndex * 9, 0, 9, 9));
}

void Soap::updateLogic() {
    Entity::updateLogic();
    this->accY++;
    annimationTimer++;
    if (annimationTimer > 15) {
        annimationIndex = annimationIndex + 1;
        annimationIndex = annimationIndex % 4;
        annimationTimer = 0;
        update();
    }
}

void Soap::setPosition(int x, int y) {
    setX(x); setY(y);
}

bool Soap::handleInput() {
    return true;
}

void Soap::hit(GameObject* what, Direction fromDir) {
    Inert* inert = dynamic_cast<Inert*>(what);
    if (inert != nullptr && inert->isCollidable()) {
        this->dead = true;
        this->toRemove = true;
    }
    Ennemy * ennemy = dynamic_cast<Ennemy *>(what);
    if (ennemy != nullptr) {
        ennemy->hurt();
        this->dead = true;
        this->toRemove = true;
    }
}
