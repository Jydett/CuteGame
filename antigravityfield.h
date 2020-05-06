#ifndef ANTIGRAVITYFIELD_H
#define ANTIGRAVITYFIELD_H

#include <QGraphicsRectItem>


class AntigravityField : public QGraphicsRectItem
{
public:
    AntigravityField();
    enum { Type = UserType + 1 };
    int type() const { return Type; };

private:
    QColor color;
};

#endif // ANTIGRAVITYFIELD_H
