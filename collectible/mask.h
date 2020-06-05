#ifndef MASK_H
#define MASK_H
#include "../core/inert.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include "../entities/player.h"

class Mask: public Inert, public QGraphicsRectItem
{
public:
    Mask();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
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
