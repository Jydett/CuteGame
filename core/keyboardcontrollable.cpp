#include "keyboardcontrollable.h"
#include <QDebug>
#include <QKeyEvent>
#include "../scene/playscene.h"

KeyBoardControllable::KeyBoardControllable() {
    leftKeyPressed = false;
    rightKeyPressed = false;
    spaceKeyPressed = false;
    downKeyPressed = false;
}

void KeyBoardControllable::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) {
        event->ignore();
    } else {
        //    qDebug() << "Key pressed event " << event->key();
        if (event->key() == Qt::Key_Left) {
            leftKeyPressed = true;
        } else if (event->key() == Qt::Key_Right) {
            rightKeyPressed = true;
        } else if (event->key() == Qt::Key_Space) {
            spaceKeyPressed = true;
        } else if (event->key() == Qt::Key_Down) {
            downKeyPressed = true;
        } else if (event->key() == Qt::Key_B) {
            qDebug() << "Key pressed event " << event->key();
            PlayScene::showBoundingBoxes = ! PlayScene::showBoundingBoxes;
        }
    }
}

void KeyBoardControllable::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) {
        event->ignore();
    } else {
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
}
