#ifndef SQUARE_H
#define SQUARE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Tile;
class Square : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Tile* tile MEMBER m_tile NOTIFY tileChanged)
public:
    Square(Tile* itile = 0);
    ~Square();
    Tile* m_tile;  // pointer to Tile object
signals:
    void tileChanged(Tile* newTile);
    void going_to_delete();


public slots:
    void slot_erase();
};

#endif // SQUARE_H
