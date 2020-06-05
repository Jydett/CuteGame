#include "thug.h"
#include "../scene/playscene.h"
#include "spit.h"
#include <QPainter>

#define INITIAL_SPIT 300
#define TIME_SPIT_ANIM 70
#define TIME_SPIT 40

Thug::Thug() : Ennemy(":/assets/images/caillera.png", 16, 28) {
    spitTimer = INITIAL_SPIT;
    life = 2;
}

void Thug::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    int yOffset = 0;
    if (spitTimer < TIME_SPIT_ANIM) {
        yOffset = height * 2;
    }
    if (PlayScene::showBoundingBoxes) {
        painter->drawRect(rect().toAlignedRect());
    }
    if (invincibilityFrames == 0 || invincibilityFrames % 5 == 0) {
        QPointF pos = boundingRect().topLeft();
        painter->drawPixmap(
            QPointF(pos.x(), pos.y()),
            textureData,
            QRectF(annimationIndex * width, (-direction + 1) / 2 * height + yOffset, width, height)
        );
    }
}

void Thug::updateLogic() {
    Ennemy::updateLogic();
    spitTimer--;
    if (spitTimer < 0) {
        spitTimer = INITIAL_SPIT + PlayScene::randInt(0, 300);
    }
    if (spitTimer == TIME_SPIT) {
        Spit * spit = new Spit(direction);
        QPointF p;
        if (direction == 1) {
            p = rect().topRight();
        } else {
            p = rect().topLeft();
        }
        p = mapToScene(p);
        spit->setPosition(p.x(), p.y() + height / 3);
        scene()->addItem(spit);
    }
}
