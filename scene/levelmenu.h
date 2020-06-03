#ifndef LEVELMENU_H
#define LEVELMENU_H

#include <QString>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsView>

#include <QTimer>

#include <button.h>
#include "scene/playscene.h"
#include "view/levelview.h"
#include "player/player.h"


class LevelMenu: public QGraphicsView{
    Q_OBJECT
private:
    void closeEvent(QCloseEvent *event) override;
public:
    LevelMenu(QWidget* parent = NULL);
    void displayLevelMenu();
    void start(QString path);

public slots:
    void startLevel1();
    void startLevel2();
    void startLevel3();
    void startLevelF();

private:
    QGraphicsScene* scene;
};

#endif // LEVELMENU_H
