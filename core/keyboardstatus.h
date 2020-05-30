#ifndef KEYBOARDSTATUS_H
#define KEYBOARDSTATUS_H
#include <QKeyEvent>

class KeyBoardStatus
{
public:
    KeyBoardStatus();

    bool rightKeyPressed;
    bool leftKeyPressed;
    bool spaceKeyPressed;
    bool downKeyPressed;
    bool shiftKeyPressed;


    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // KEYBOARDSTATUS_H
