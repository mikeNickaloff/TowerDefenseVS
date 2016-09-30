#ifndef WALL_H
#define WALL_H

#include <QtCore/qglobal.h>
#include <QObject>
class Tile;

class Wall : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Tile* tile MEMBER m_tile NOTIFY tileChanged)
public:
    Wall(Tile* itile = 0);
    Tile* m_tile;  // pointer to Tile object

signals:
    void tileChanged(Tile* newTile);
};

#endif // WALL_H
