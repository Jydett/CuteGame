#include "player.h"
#include <QDebug>
#include "../surpriseblock.h"

#define SPEED 3

Player::Player(QGraphicsView* view)
{
    this->view = view;
    setRect(0, 0, 16, 32);
    generateCollisionBox();
//    setFlag(ItemClipsToShape);
    image = QImage(":/assets/images/player.png");
    if (image.format() == 0) {
        qDebug() << "ERREUR DE CHARGEMENT DE L'IMAGE";
    }
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QRectF rect = this->rect();
//    text->setPlainText("x:" + QString::number(x()) + " y:" + QString::number(y()) +
//                       "\nsx:" + QString::number(speedX) + " sy:" + QString::number(speedY) +
//                       "\nsy:" + QString::number(accX) + " ay:" + QString::number(accY) +
//                       "\n jumping ? " + QString::number(jumping) + " requested ? " + QString::number(jumpRequested) +
////                       "\n bottom " + QString::number(contactYbottom) + " top " + QString::number(contactYtop)
////                       "\n scroll " + scroll->value()
//                       "");
//    painter->drawRect(rect.toAlignedRect());
    painter->drawImage(rect, image);

//     painter->setBrush(QBrush(Qt::red));
//    for (auto i = 0; i < 8; i++) {
//        painter->drawPoint(collisionPoints[i]);
//    }
}

void Player::movementUpdated(qreal dX, qreal dY) {
    auto const CONST_Y = 400;
    view->centerOn(x(), CONST_Y);
}

void Player::hit(GameObject *what, Direction fromDir) {
    SurpriseBlock * block = dynamic_cast<SurpriseBlock*>(what);
    qDebug() << "cast: " << dynamic_cast<SurpriseBlock*>(what) << " res" << block;
    if (block) {
        block->collide(this);
    }
    qDebug() << "player hit";
}
