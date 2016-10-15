#ifndef ASTARPATH_H
#define ASTARPATH_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QList>
#include <QPair>
#include <QObject>
#include <QHash>
class Board;
class Tile;
class Entity;
class Enemy;
class Gun;
class Square;
class Wall;
class Path;

class Entrance;
class Exit;
class AStarPath : public QObject
{
    Q_OBJECT
public:
    explicit AStarPath(QObject *parent = 0, Board* i_board = 0);
    QList<Tile*> openSet;
    QList<Tile*> closedSet;
    QHash<Tile*, Tile*> cameFrom;
    QHash<Tile*, int> gScore;
        QHash<Tile*, int> fScore;
        Board* m_board;
signals:

public slots:
    QList<Tile*> find_path(Tile* i_start, Tile* i_end);
    QList<Tile*> reconstruct_path(Tile* i_end);
};

#endif // ASTARPATH_H

