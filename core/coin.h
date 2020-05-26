#ifndef COIN_H
#define COIN_H
#include "inert.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include "../player/player.h"


class Coin : public Inert, public QGraphicsRectItem
{
public:
    Coin();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    enum { Type = COIN_TYPE };
    int type() const override { return Type; };
    void setPosition(int x, int y);
protected:
    void hit(GameObject* what, Direction fromDir) override;

private:
    bool collected;
    QPixmap textureData;
};

#endif // COIN_H
