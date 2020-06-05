#include "levelview.h"
#include <QWheelEvent>
#include "scene/levelmenu.h"

void LevelView::closeEvent(QCloseEvent *event) {
    scene()->clear();
    emit lvlViewClosed();
}

LevelView::LevelView() {
    this->setFixedSize(QSize(1280, 720));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHints(QPainter::SmoothPixmapTransform);
    this->setSceneRect(0, 0, 10000, 225);
    this->scale(1.4, 1.4);
    this->keyboardStatus = new KeyBoardStatus();

    //add the music
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    music.playMusic(10);
}

LevelView::~LevelView() {
    delete keyboardStatus;
}

void LevelView::sceneSet(QGraphicsScene *scene) {
    setScene(scene);
    emit sceneChanged();
}

void LevelView::wheelEvent(QWheelEvent *e)
{
    if (e->delta() > 0) {
        scale(1.1, 1.1);
    } else {
        scale(1/1.1, 1/1.1);
    }
}

void LevelView::keyPressEvent(QKeyEvent *event) {
    keyboardStatus->keyPressEvent(event);
}

void LevelView::keyReleaseEvent(QKeyEvent *event) {
    keyboardStatus->keyReleaseEvent(event);
}
