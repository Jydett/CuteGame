#include "button.h"
#include <QBrush>
#include <QGraphicsTextItem>
#include <QGraphicsItem>

button::button(QString text, QGraphicsItem *parent): QGraphicsRectItem(parent) {
    //set style and color of the button
    setRect(0, 0, 200, 30);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::magenta);
    setBrush(brush);

    // set name and position
    name = new QGraphicsTextItem(text, this);
    int x = rect().width()/2 - (*name).boundingRect().width()/2;
    int y = rect().height()/2 - (*name).boundingRect().height()/2;
    (*name).setPos(x, y);

    // set hover true
    setAcceptHoverEvents(true);
}

void button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit clicked();
}

void button::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    // change color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkMagenta);
    setBrush(brush);
}

void button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    // change color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::magenta);
    setBrush(brush);
}

