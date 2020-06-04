#include "levelview.h"
#include <QWheelEvent>
#include "scene/levelmenu.h"

void LevelView::closeEvent(QCloseEvent *event)
{
    /*LevelMenu* levelMenu = new LevelMenu();
    levelMenu->show();
    levelMenu->displayLevelMenu();*/
    emit lvlViewClosed();

}

LevelView::LevelView()
{
//    bgm = new QMediaPlaylist;
    this->setFixedSize(QSize(1280, 720));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHints(QPainter::SmoothPixmapTransform);
    this->setSceneRect(0, 0, 10000, 225);
    this->scale(1.4, 1.4);
    this->keyboardStatus = new KeyBoardStatus();


    //add the music
    music = new Music();
    music->playMusic(10);

    this->setAttribute(Qt::WA_DeleteOnClose, true);
}

LevelView::~LevelView() {
    delete keyboardStatus;
}

void LevelView::stop()
{
    dynamic_cast<PlayScene*>(scene())->stopTimer();
    delete(music);
}

void LevelView::sceneSet(QGraphicsScene *scene) {
    setScene(scene);
    emit sceneChanged();
}

void LevelView::drawForeground(QPainter *painter, const QRectF &rect)
{
    painter->drawText(mapToScene(30, 30), "Score : 0");
}

void LevelView::wheelEvent(QWheelEvent *e)
{
    //TODO max zoom ?
    if(e->delta() > 0)
        scale(1.1, 1.1);
    else
        scale(1/1.1, 1/1.1);
}

void LevelView::keyPressEvent(QKeyEvent *event) {
    keyboardStatus->keyPressEvent(event);
}

void LevelView::keyReleaseEvent(QKeyEvent *event) {
    keyboardStatus->keyReleaseEvent(event);
}
