#include "levelview.h"
#include <QWheelEvent>

LevelView::LevelView()
{
//    bgm = new QMediaPlaylist;
    this->setFixedSize(QSize(1280, 720));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHints(QPainter::SmoothPixmapTransform);
    this->setSceneRect(0, 0, 10000, 225);
    this->scale(1.4, 1.4);
}

void LevelView::sceneSet(QGraphicsScene *scene) {
    setScene(scene);
    emit sceneChanged();
}

void LevelView::wheelEvent(QWheelEvent *e)
{
    //TODO max zoom ?
    if(e->delta() > 0)
        scale(1.1, 1.1);
    else
        scale(1/1.1, 1/1.1);
}
