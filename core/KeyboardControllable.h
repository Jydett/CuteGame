#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

#include "PhysicsObject.h"

class KeyBoardControllable : public PhysicsObject
{
public:
    KeyBoardControllable();

protected:
    bool handleInput() override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    bool rightKeyPressed;
    bool leftKeyPressed;
    bool spaceKeyPressed;
};

#endif // CONTROLLABLE_H
