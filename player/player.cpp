#include "player.h"
#include <QDebug>
#include <typeinfo>
#include "../surpriseblock.h"
#include "../scene/playscene.h"
#include "../core/keyboardstatus.h"
#include "../core/soap.h"
#include <QApplication>

#define SPEED 3

#define DEBUG

Player::Player(LevelView* view)
{
    this->view = view;
    this->spriteWidth = 16;
    this->spriteHeight = 32;
    this->annimationIndex = 0;
    this->lastDirection = 1;

    this->annimationTimer = 0;
    setRect(0, 0, 16, 32);
    generateCollisionBox();
    this->debugIfo = new QGraphicsTextItem(this);
    textureData = QPixmap(":/assets/images/player.png");
     //TODO gerer erreur
    this->downKeyPressedLastFrame = false;
    this->isCrouching = false;

    this->soapBar = new QGraphicsRectItem(this);
    soapBar->setRect(0, - 10, 16, 3);
    soapBar->setBrush(QColor(0xFF, 0xae, 0xc8));

    this->soapCount = 0;

    isMasked = false;
    life = 3;
    shootTimer = 0;
    invincibilityFrames = 0;

}

void Player::updateLogic() {
    if (dead) {
        dead = false;
        setPosition(0, 0);
        speedX = 0;
        speedY = 0;
        isMasked = false;
    }
    Entity::updateLogic();
    xIndex = 0, yIndex = 0;
    if (isCrouching) {
        spriteHeight = 16;
        yIndex = 32 + 1 + 32 + 2;
        xIndex = lastDirection * spriteWidth;
    } else {
        annimationTimer++;
        if (annimationTimer > 6) {
            annimationIndex = ((annimationIndex + 1) % 3);
            annimationTimer = 0;
        }

        spriteHeight = 32;
        if (speedX > 0) {
            xIndex = ((annimationIndex + 1) % 3) * spriteWidth;
        } else if (speedX < 0) {
            xIndex = ((annimationIndex + 1) % 3) * spriteWidth;
            yIndex = spriteHeight + 1;
        } else {
            annimationIndex = 0;
            yIndex = lastDirection * (spriteHeight + 1);
        }
    }

    if (isMasked) {
        yIndex += 84;
    }

    if (shootTimer > 50) {
        xIndex = 64;
    }

    if (shootTimer > 0) {
        shootTimer--;
    }

    if (soapCount > 0) {
        soapBar->setVisible(true);
        QRectF old = soapBar->rect();
        soapBar->setRect(old.x(), old.y(), soapCount * 3, 3);
    } else {
        soapBar->setVisible(false);
    }
    if (invincibilityFrames > 0) {
        invincibilityFrames--;
    }

    if(dying){
        yIndex = 0;
        xIndex = 80;
        if (life > 0) {
            QString lifeRemaining = QString("life : %1").arg(life);
            qDebug() << lifeRemaining;
            dying = false;
            Player::setPosition(0,0);
        }
        else {
            dying = false;
            dead = true;
        }
    }
}

void Player::shoot() {
    if (soapCount > 0 && shootTimer == 0 && ! isCrouching) {
        soapCount--;
        shootTimer = 60;

        sound.playSound(4, 40);
        Soap* soap = new Soap(! (bool)lastDirection);
        soap->setPosition(this->x(), this->y() + 10);
        this->scene()->addItem(dynamic_cast<QGraphicsItem *>(soap));
    }
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QRectF rect = this->rect();

    if (invincibilityFrames == 0 || invincibilityFrames % 10 == 0) {
        painter->drawPixmap(rect, textureData, QRect(xIndex, yIndex, spriteWidth, spriteHeight));
    }

    if (PlayScene::showBoundingBoxes)
        painter->drawRect(rect.toAlignedRect());
}

void Player::movementUpdated(qreal dX, qreal dY) {
    auto const CONST_Y = 400;
    view->centerOn(x(), CONST_Y);
}

void Player::hit(GameObject* what, Direction fromDir) {
    if (what == nullptr) return;
    what->hit(this, oposite(fromDir));
}

void Player::setPosition(int x, int y) {
    movementUpdated(this->x() - x, this->y() - y);
    setX(x); setY(y);
    setRect(x, y, 16, 32);
}

void Player::jump() {
    sound.playSound(0,30);
    jumping = true;
    jumpRequested = true;
    speedY = -jumpForce;
}

bool Player::handleInput() {
    bool moveRequested = false;

    KeyBoardStatus* kbs = view->keyboardStatus;

    isCrouching = kbs->downKeyPressed;

    if (kbs->leftKeyPressed) {
        lastDirection = 1;
     }
     if (kbs->rightKeyPressed) {
         lastDirection = 0;
     }
    if (! (isCrouching && wasOnGroundLastFrame)) {
       if (kbs->leftKeyPressed) {
            speedX -= linearMovement(accX);
            moveRequested = true;
        }
        if (kbs->rightKeyPressed) {
            speedX += linearMovement(accX);
            moveRequested = true;
        }
    }

    if (isCrouching != downKeyPressedLastFrame) {
        if (isCrouching) {
            setY(y() + 16);
            setRect(0, 0, 16, 16);
        } else {
            setY(y() - 16);
            setRect(0, 0, 16, 32);
        }
        //TODO optimisation passer d'une bb à l'autre sans la regenerer
        generateCollisionBox();
    }
    //TODO pas refresh a chaque fois
    QGraphicsRectItem::update(rect());
    downKeyPressedLastFrame = kbs->downKeyPressed;

    if (kbs->spaceKeyPressed && wasOnGroundLastFrame && !jumping && !jumpRequested) {
        jump();
    }

    if (! kbs->spaceKeyPressed) {
        jumpRequested = false;
    }

    if (kbs->shiftKeyPressed) {
        shoot();
    }

    return moveRequested;
}

void Player::collectSoap() {
    sound.playSound(1, 30);
    soapCount++;
}

void Player::collectMask() {
    sound.playSound(6, 100);
    isMasked=true;
}

void Player::collectToiletPaper() {
    sound.playSound(5, 100);
    isMasked=true;
}

void Player::hurt(GameObject* byWhat) {
    if (invincibilityFrames > 0) return;
    sound.playSound(3,40);
    if (isMasked) {
        isMasked = false;
        //apply knockback
        Entity * byWhayEntity = dynamic_cast<Entity *>(byWhat);
        if (byWhayEntity != nullptr) {
            this->speedX = byWhayEntity->sx() / 3;
            this->speedY = byWhayEntity->sy() / 3;
        }
        invincibilityFrames = 20;
    } else {
        qDebug() << "dead";
        dying = true;
        soapCount = 0;
        if (life > 0) {
            life--;
        }
    }
}
