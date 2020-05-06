#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView {
    Q_OBJECT
signals:
    void sceneChanged();

public:
//    QMediaPlaylist *bgm;

    View();
    void sceneSet(QGraphicsScene * scene);
};

#endif // VIEW_H
