#ifndef TOILETPAPER_H
#define TOILETPAPER_H

#include "inert.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QGraphicsScene>

class ToiletPaper : public Inert, public QGraphicsRectItem
{
public:
    ToiletPaper();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    enum { Type = COIN_TYPE };//FIXME cointype
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
    QPixmap textureData;
};
#endif // TOILETPAPER_H
