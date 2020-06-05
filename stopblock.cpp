#include "stopblock.h"
#include "scene/playscene.h"
#include <QPainter>

StopBlock::StopBlock() {
    this->collidable = false;
    setRect(0, 0, 16, 16);
}

void StopBlock::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    if (PlayScene::showBoundingBoxes) {
        painter->drawRect(rect());
    }
}

void StopBlock::setPosition(int x, int y) {
    setRect(x, y, 16, 16);
}

