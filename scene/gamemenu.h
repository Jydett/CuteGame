#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QString>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsView>

#include <QTimer>

#include <button.h>
#include "scene/levelmenu.h"

class gameMenu: public QGraphicsView{
    Q_OBJECT
private:
    void closeEvent(QCloseEvent *event) override;
public:
    gameMenu(QWidget* parent = NULL);
    void displayMainMenu();

public slots:
    void start();

private:
    QGraphicsScene* scene;
};

#endif // GAMEMENU_H
