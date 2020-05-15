#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

#include "physicsobject.h"
#include "sound/sound.h"

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
    Sound * sound;
};

#endif // CONTROLLABLE_H
