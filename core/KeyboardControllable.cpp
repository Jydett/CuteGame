#include "KeyboardControllable.h"

#include <QDebug>
#include <QKeyEvent>

KeyBoardControllable::KeyBoardControllable() {
    leftKeyPressed = false;
    rightKeyPressed = false;
    spaceKeyPressed = false;
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
    }
}


bool KeyBoardControllable::handleInput() {
    bool moveRequested = false;
//    qDebug() << "handleInput";
    if (leftKeyPressed) {
        speedX -= accX;
        moveRequested = true;
    }
    if (rightKeyPressed) {
        speedX += accX;
        moveRequested = true;
    }
    if (spaceKeyPressed && !jumping && !jumpRequested) {
        jumping = true;
        jumpRequested = true;
        speedY = -jumpForce;
    }
    if (! spaceKeyPressed) {
        jumpRequested = false;
    }
    return moveRequested;
}
