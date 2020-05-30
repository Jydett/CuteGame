#include "keyboardstatus.h"
#include "../scene/playscene.h"
#include <QDebug>

KeyBoardStatus::KeyBoardStatus()
{
    this->leftKeyPressed = false;
    this->rightKeyPressed = false;
    this->downKeyPressed = false;
    this->spaceKeyPressed =false;
}

void KeyBoardStatus::keyPressEvent(QKeyEvent *event)
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
        } else if (event->key() == Qt::Key_Shift) {
            shiftKeyPressed = true;
        }
    }
}

void KeyBoardStatus::keyReleaseEvent(QKeyEvent *event)
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
        } else if (event->key() == Qt::Key_Shift) {
            shiftKeyPressed = false;
        }
    }
}
