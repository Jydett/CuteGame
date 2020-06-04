#include "toiletpaper.h"
#include "../player/player.h"
#include <QPainter>
#include "../scene/playscene.h"

ToiletPaper::ToiletPaper()
{
    collidable = false;
    setRect(0, 0, 15, 16);
    this->textureData = QPixmap(":/assets/images/pq.png");
}

void ToiletPaper::setPosition(int x, int y) {
    setRect(x, y, 15, 16);
}

void ToiletPaper::paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF pos = rect().topLeft();
    painter->drawPixmap(
            QPointF(pos.x(), pos.y()),
            textureData,
            QRectF(0, 0, 15, 16)
    );
    if (PlayScene::showBoundingBoxes)
        painter->drawRect(rect());
}

void ToiletPaper::hit(GameObject *what, Direction fromDir)
{
    Player* player = dynamic_cast<Player*>(what);
    if (! toRemove && player != nullptr) {

        //TODO nextLevel
        toRemove = true;
        emit nextLevel();
        return;
    }
}

