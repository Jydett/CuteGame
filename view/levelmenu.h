#ifndef LEVELMENU_H
#define LEVELMENU_H

#include <QString>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsView>

#include <QTimer>

#include "scene/ui/button.h"
#include "scene/playscene.h"
#include "view/levelview.h"
#include "entities/player.h"


class LevelMenu: public QGraphicsView{
    Q_OBJECT
private:
    void closeEvent(QCloseEvent *event) override;
public:
    LevelMenu(QWidget* parent = NULL, QGraphicsScene* scene = NULL);
    void displayLevelMenu(QGraphicsScene* scene);
    void start(QString path);

public slots:
    void startLevel1();
    void startLevel2();
    void startLevel3();
    void startLevel4();
    void startLevel5();
    void startLevelF();
    void retour();

signals:
    void displayLevel1();
    void displayLevel2();
    void displayLevel3();
    void displayLevel4();
    void displayLevel5();
    void displayLevelF();
    void lvlMenuClosed();
    void returnToMainMenu();
};

#endif // LEVELMENU_H
