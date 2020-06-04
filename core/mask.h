#ifndef MASK_H
#define MASK_H
#include "inert.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include "../player/player.h"

class Mask: public Inert, public QGraphicsRectItem
{
public:
    Mask();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    enum { Type = COIN_TYPE };
    int type() const override { return Type; };
    void setPosition(int x, int y) override;
    void remove() override {
        scene()->removeItem(this);
    }
    void advance(int step) override {
        if (! step) {
            GameObject::updateLogic();
        }
    };
protected:
    void hit(GameObject* what, Direction fromDir) override;

private:
    bool collected;
    QPixmap textureData;
};
#endif // MASK_H
