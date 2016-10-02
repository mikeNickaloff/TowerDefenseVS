#ifndef PATHTHREAD_H
#define PATHTHREAD_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QThread>

class Board;
class Tile;
class Entrance;
class Exit;
class Path;
class PathThread : public QThread
{
    Q_OBJECT
public:
    explicit PathThread(QObject *parent = 0, Board* i_board = 0);
    Board* m_board;
    Tile* m_tile;
    int distance_between(Tile* tile1, Tile* tile2);
    bool m_found_path;
    Entrance* m_entrance;
signals:

public slots:
    void run();
    void iterate_neighbors(Tile* cur_tile, QList<Tile*> previous_tiles);
};

#endif // PATHTHREAD_H
