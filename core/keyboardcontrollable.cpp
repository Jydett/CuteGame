#include "keyboardcontrollable.h"
#include <QDebug>
#include <QKeyEvent>

KeyBoardControllable::KeyBoardControllable() {
    leftKeyPressed = false;
    rightKeyPressed = false;
    spaceKeyPressed = false;
    downKeyPressed = false;
}

void KeyBoardControllable::keyPressEvent(QKeyEvent *event)
{
//    qDebug() << "Key pressed event";
    if (event->key() == Qt::Key_Left) {
        leftKeyPressed = true;
    } else if (event->key() == Qt::Key_Right) {
        rightKeyPressed = true;
    } else if (event->key() == Qt::Key_Space) {
        spaceKeyPressed = true;
    } else if (event->key() == Qt::Key_Down) {
        downKeyPressed = true;
    }
}

void KeyBoardControllable::keyReleaseEvent(QKeyEvent *event)
{
//    qDebug() << "Key released event";
    if (event->key() == Qt::Key_Left) {
        leftKeyPressed = false;
    } else if (event->key() == Qt::Key_Right) {
        rightKeyPressed = false;
    } else if (event->key() == Qt::Key_Space) {
        spaceKeyPressed = false;
    } else if (event->key() == Qt::Key_Down) {
        downKeyPressed = false;
    }
}


bool KeyBoardControllable::handleInput() {
    bool moveRequested = false;
    if (leftKeyPressed) {
        speedX -= linearMovement(accX);
        moveRequested = true;
    }
    if (rightKeyPressed) {
        speedX += linearMovement(accX);
        moveRequested = true;
    }
    if (spaceKeyPressed && !jumping && !jumpRequested) {
        if (onJump()) {
            jumping = true;
            jumpRequested = true;
            speedY = -jumpForce;
        }
    }
    if (! spaceKeyPressed) {
        jumpRequested = false;
    }
    return moveRequested;
}
