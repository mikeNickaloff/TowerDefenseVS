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
class Square;
class Entity;
class Enemy;
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
    Entity* m_entity;
    int High;
    int Low;
    int random_num;
    QList<Tile*> compress_list(QList<Tile*> inp_list);
     qint64 start_time;
     bool m_blocked_path;
signals:
     void place_last_gun(bool shouldPlace);
public slots:
    void run();
    void iterate_neighbors(Tile* cur_tile, QList<Tile*> i_previous_tiles, Tile* start_tile);

};

#endif // PATHTHREAD_H
