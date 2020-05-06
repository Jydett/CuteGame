#include "player.h"
#include <QPainter>
#include <QDebug>
#include <QRectF>

#define SPEED 3

Player::Player()
{
    setRect(0, 0, 20, 40);
    generateCollisionBox();
//    setFlag(ItemClipsToShape);
//    mPixmap = QPixmap(":images/player.png");
    /*image = QImage("player.png");
    if (image.format() == 0) {
        qDebug() << "ERREUR DE CHARGEMENT DE L'IMAGE";
    }*/
    text = new QGraphicsTextItem(this);
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QRectF rect = this->rect();
    text->setPlainText("x:" + QString::number(x()) + " y:" + QString::number(y()) +
                       "\nsx:" + QString::number(speedX) + " sy:" + QString::number(speedY) +
                       "\nsy:" + QString::number(accX) + " ay:" + QString::number(accY) +
                       "\n jumping ? " + QString::number(jumping) + " requested ? " + QString::number(jumpRequested) +
//                       "\n bottom " + QString::number(contactYbottom) + " top " + QString::number(contactYtop)
                       "");
    painter->drawRect(rect.toAlignedRect());
}
