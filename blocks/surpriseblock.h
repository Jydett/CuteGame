#ifndef SURPRISEBLOCK_H
#define SURPRISEBLOCK_H
#include <QGraphicsRectItem>
#include "../core/inert.h"
#include <QGraphicsScene>

class SurpriseBlock : public Inert, public QGraphicsRectItem
{
public:
    SurpriseBlock(bool hidden, GameObject* toSpawn);
    ~SurpriseBlock();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setPosition(int x, int y) override;
    void hit(GameObject *what, Direction fromDir) override;
    void remove() override {
        scene()->removeItem(this);
    }

private:
    QPixmap textureData;
    int size;
    bool broken;
    bool deleteOnbreak;
    int brokenOffset;
    bool hidden;
    GameObject* toSpawn;
};

#endif // SURPRISEBLOCK_H
