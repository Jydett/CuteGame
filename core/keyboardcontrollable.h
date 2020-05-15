#ifndef KEYBOARDCONTROLLABLE2_H
#define KEYBOARDCONTROLLABLE2_H
#include "entity.h"
#include <QKeyEvent>

class KeyBoardControllable : public Entity
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

#endif // KEYBOARDCONTROLLABLE2_H