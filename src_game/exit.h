#ifndef EXIT_H
#define EXIT_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
class Tile;
class Exit : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Tile* tile MEMBER m_tile NOTIFY tileChanged)
public:
    Exit(Tile* itile = 0);
    Tile* m_tile;  // pointer to Tile object
signals:
    void tileChanged(Tile* newTile);
};

#endif // EXIT_H
