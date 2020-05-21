#include "player.h"
#include <QDebug>
#include <typeinfo>
#include "../surpriseblock.h"

#define SPEED 3

Player::Player(QGraphicsView* view)
{
    this->view = view;
    this->spriteWidth = 16;
    this->spriteHeight = 32;
    this->annimationIndex = 0;
    this->lastYIndex = 0;
    setRect(0, 0, 16, 32);
    generateCollisionBox();
    axeXSave = accX;
//    this->debugIfo = new QGraphicsTextItem(this);
//    setFlag(ItemClipsToShape);
    textureData = QPixmap(":/assets/images/player.png");
     //TODO gerer erreur
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QRectF rect = this->rect();
    int xIndex = 0, yIndex = 0;
    int actualSpriteHeight;
    if (downKeyPressed) {
        if (accX != 0) {
            axeXSave = accX;
        }
        accX = 0;
        actualSpriteHeight = 16;
        yIndex = spriteHeight + 1 + spriteHeight + 2;
        rect = QRectF(rect.x(), rect.y() + actualSpriteHeight, spriteWidth, actualSpriteHeight);
        if (speedX < 0) {
            xIndex = spriteWidth;
        }
    } else {
        accX = axeXSave;
        actualSpriteHeight = spriteHeight;
        if (speedX > 0) {
            xIndex = (annimationIndex++ % 3 + 1) * spriteWidth;
        } else if (speedX < 0) {
            xIndex = (annimationIndex++ % 3 + 1) * spriteWidth;
            yIndex = spriteHeight + 1;
        } else {
            yIndex = lastYIndex;
        }
    }
    lastYIndex = yIndex;

    painter->drawPixmap(rect, textureData, QRect(xIndex, yIndex, spriteWidth, actualSpriteHeight));

//     painter->setBrush(QBrush(Qt::red));
//    for (auto i = 0; i < 8; i++) {
//        painter->drawPoint(collisionPoints[i]);
//    }

    //DEBUG
    {
//        painter->drawRect(rect.toAlignedRect());


//        debugIfo->setPlainText(
    //        "x:" + QString::number(x()) + " y:" + QString::number(y()) +
    //       "\nsx:" + QString::number(speedX) + " sy:" + QString::number(speedY) +
    //       "\nsy:" + QString::number(accX) + " ay:" + QString::number(accY) +
    //       "\n jumping ? " + QString::number(jumping) + " requested ? " + QString::number(jumpRequested) +
//           " \n wasOnGround " + QString::number(wasOnGroundLastFrame) +
    //                       "\n bottom " + QString::number(contactYbottom) + " top " + QString::number(contactYtop)
    //                       "\n scroll " + scroll->value()
//           "");
    }
}

void Player::movementUpdated(qreal dX, qreal dY) {
    auto const CONST_Y = 400;
    view->centerOn(x(), CONST_Y);
}

void Player::hit(GameObject* what, Direction fromDir) {
    SurpriseBlock* block = dynamic_cast<SurpriseBlock*>(what);
    if (block != nullptr && fromDir == TOP) {
        block->collide(this);
        return;
    }
}

bool Player::onJump() {
    //son
    return true;
}
