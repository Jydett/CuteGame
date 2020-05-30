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
    virtual ~GameObject() {};

    inline bool isCollidable() {
        return collidable;
    }

    inline qreal linearMovement(qreal pps/*, int delta*/) const {
        static const qreal sec_elapsed = 1.0 / 60.0;//TODO get delta
        return pps * sec_elapsed;
    }

    Direction oposite(Direction dir) const {
        switch (dir) {
            case SIDE: return SIDE;
            case TOP: return BOTTOM;
            case BOTTOM: return TOP;
        }
        return SIDE;
    }

    virtual void updateLogic() {
        if (toRemove) {
            remove();
            delete this;
        }
    }

    virtual void remove() = 0;
    virtual void setPosition(int x, int y) = 0;

    virtual void hit(GameObject* what, Direction fromDir) {};
protected:
    bool collidable;
    bool toRemove;
};

#endif // GAMEOBJECT_H
