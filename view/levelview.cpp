#include "levelview.h"

LevelView::LevelView()
{
//    bgm = new QMediaPlaylist;
    this->setFixedSize(QSize(1280, 720));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void LevelView::sceneSet(QGraphicsScene *scene) {
    setScene(scene);
    emit sceneChanged();
}
