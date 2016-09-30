#ifndef ENTRANCE_H
#define ENTRANCE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Tile;

class Entrance : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Tile* tile MEMBER m_tile NOTIFY tileChanged)
public:
    explicit Entrance(Tile* itile = 0, QObject* parent = 0);
    Tile* m_tile;  // pointer to Tile object
signals:
    void tileChanged(Tile* newTile);
};
#endif // ENTRANCE_H
