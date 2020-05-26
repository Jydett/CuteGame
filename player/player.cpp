#include "player.h"
#include <QDebug>
#include <typeinfo>
#include "../surpriseblock.h"
#include "../scene/playscene.h"
#include "../core/keyboardstatus.h"
#include <QApplication>

#define SPEED 3

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
//    setFlag(ItemClipsToShape);
    textureData = QPixmap(":/assets/images/player.png");
     //TODO gerer erreur
    this->downKeyPressedLastFrame = false;
    this->isCrouching = false;
}

void Player::update() {
    Entity::update();
    qDebug() << "focussed" << QApplication::focusWidget();
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QRectF rect = this->rect();
    int xIndex = 0, yIndex = 0;
    int actualSpriteHeight;
    if (isCrouching) {
        actualSpriteHeight = 16;
        yIndex = spriteHeight + 1 + spriteHeight + 2;
        xIndex = lastDirection * spriteWidth;
    } else {
        annimationTimer++;
        if (annimationTimer > 300) {
            annimationIndex = ((annimationIndex + 1) % 3);
            annimationTimer = 0;
        }

        actualSpriteHeight = spriteHeight;
        if (speedX > 0) {
            xIndex = (annimationIndex + 1) * spriteWidth;
        } else if (speedX < 0) {
            xIndex = (annimationIndex + 1) * spriteWidth;
            yIndex = spriteHeight + 1;
        } else {
            annimationIndex = 0;
            yIndex = lastDirection * (spriteHeight + 1);
        }
    }

    if (speedX > 0) {
        lastDirection = 0;
    } else if (speedX < 0) {
        lastDirection = 1;
    }

    painter->drawPixmap(rect, textureData, QRect(xIndex, yIndex, spriteWidth, actualSpriteHeight));

    if (PlayScene::showBoundingBoxes)
        painter->drawRect(rect.toAlignedRect());

    #ifdef DEBUG

//        painter->setBrush(QBrush(Qt::white));
    debugIfo->setPlainText(
////            "x:" + QString::number(x()) + " y:" + QString::number(y()) +
//    //       "\nsx:" + QString::number(speedX) + " sy:" + QString::number(speedY) +
//    //       "\nsy:" + QString::number(accX) + " ay:" + QString::number(accY) +
                "\nannimationTimer" + QString::number(annimationTimer) +
                "\nannimationIndex" + QString::number(annimationIndex) +
//           "\n jumping ? " + QString::number(jumping) +
//            " requested ? " + QString::number(jumpRequested) +
//           " \n wasOnGround " + QString::number(wasOnGroundLastFrame) +
//           " \n downKeyPressed " + QString::number(downKeyPressed) +
//           "  spaceKeyPressed " + QString::number(spaceKeyPressed) +
//    //                       "\n bottom " + QString::number(contactYbottom) + " top " + QString::number(contactYtop)
//    //                       "\n scroll " + scroll->value()
       "");
//         painter->setBrush(QBrush(Qt::red));
//        for (auto i = 0; i < 8; i++) {
//            painter->drawPoint(collisionPoints[i]);
//        }
    #endif
}

void Player::movementUpdated(qreal dX, qreal dY) {
    auto const CONST_Y = 400;
    view->centerOn(x(), CONST_Y);
}

void Player::hit(GameObject* what, Direction fromDir) {
    what->hit(this, oposite(fromDir));
}

//bool Player::onJump() {
//    //son
//    return true;
//}

bool Player::handleInput() {
    bool moveRequested = false;

    bool debugCheat = true;

    KeyBoardStatus* kbs = view->keyboardStatus;

    isCrouching = kbs->downKeyPressed;

    if (debugCheat || ! kbs->downKeyPressed) {
        if (kbs->leftKeyPressed) {
            speedX -= linearMovement(accX);
            moveRequested = true;
        }
        if (kbs->rightKeyPressed) {
            speedX += linearMovement(accX);
            moveRequested = true;
        }
    }

    //TODO deplacer ca dans la fonction update !!!!!
    if (kbs->downKeyPressed != downKeyPressedLastFrame) {
        qDebug() << "downKey status changed " << kbs->downKeyPressed << " " << rect();

        // ne marche pas ? prepareGeometryChange();
        if (kbs->downKeyPressed) {
            setY(y() + 16);
            setRect(0, 0, 16, 16);
        } else {
            //TODO faire une requete pour se lever car pas possible dans tout les cas
            setY(y() - 16);
            setRect(0, 0, 16, 32);
        }
        //TODO optimisation passer d'une bb à l'autre sans la regenerer
        generateCollisionBox();
        QGraphicsRectItem::update(rect());
    }
    downKeyPressedLastFrame = kbs->downKeyPressed;

    if (kbs->spaceKeyPressed && wasOnGroundLastFrame && !jumping && !jumpRequested) {
        if (true /*onJump()*/) {
            jumping = true;
            jumpRequested = true;
            speedY = -jumpForce;
        }
    } else if (kbs->spaceKeyPressed) {
        #ifdef DEBUG
            qDebug() << "Jump denied reason : "
                    << (! spaceKeyPressed ? "spaceKeyPressed" : "")
                    << (! wasOnGroundLastFrame ? "wasOnGroundLastFrame" : "")
                    << (jumping ? "jumping" : "")
                    << (jumpRequested ? "jumpRequested" : "");
        #endif
    }

    if (! kbs->spaceKeyPressed) {
        jumpRequested = false;
    }
    return moveRequested;
}
