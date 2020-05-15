#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class LevelView : public QGraphicsView {
    Q_OBJECT
signals:
    void sceneChanged();

public:
//    QMediaPlaylist *bgm;

    LevelView();
    void sceneSet(QGraphicsScene * scene);

protected:
    virtual void wheelEvent(QWheelEvent *e);
};

#endif // VIEW_H
