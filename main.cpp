#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QObject>
#include <QGlobal.h>
#include <QTime>
#include <QGlobal.h>
#include <QTime>

#include "scene/gamemenu.h"



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());


    gameMenu* menu = new gameMenu();
    menu->show();
    menu->displayMainMenu();

    return a.exec();
}
