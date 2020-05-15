#ifndef PLAYER2_H
#define PLAYER2_H
#include "../core/keyboardcontrollable.h"
#include <QGraphicsView>

class Player : public KeyBoardControllable
{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    Player(QGraphicsView* view);
    void movementUpdated(qreal dX, qreal dY) override;
    void hit(GameObject* what, Direction fromDir) override;

//protected:
//    bool handleInput() override;
//    void keyPressEvent(QKeyEvent* event) override;
//    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QImage image;
    QGraphicsTextItem * text;
    QGraphicsView * view;
};

#endif // PLAYER2_H
