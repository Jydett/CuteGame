#include "player.h"
#include <QPainter>
#include <QDebug>

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
}

//void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
//    painter->drawImage(rect(), image);
//}
