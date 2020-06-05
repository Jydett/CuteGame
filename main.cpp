#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QObject>
#include <qglobal.h>
#include <QTime>

#include "view/mainview.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());


    MainView* mainView = new MainView();
    mainView->show();
    mainView->display();

    return a.exec();
}
