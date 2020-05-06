#include "antigravityfield.h"
#include <QPen>
#include <QColor>
#include <QPainter>
#include <QBrush>

AntigravityField::AntigravityField()
{
    color = QColor(0xbd, 0xd7, 0xe7);

    setBrush(QBrush(color));
}

