#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <QtGlobal>
#include <QDebug>

enum Direction {
    TOP = 1,
    BOTTOM = 2,
    SIDE = 3
};

class GameObject {
public:
    GameObject();

    inline bool isCollidable() {
        return collidable;
    }

    inline qreal linearMovement(qreal pps/*, int delta*/) const {
        static const qreal sec_elapsed = 1.0 / 60.0;//TODO get delta
        return pps * sec_elapsed;
    }

    virtual void hit(GameObject* what, Direction fromDir) {};
protected:
    bool collidable;
};

#endif // GAMEOBJECT_H
