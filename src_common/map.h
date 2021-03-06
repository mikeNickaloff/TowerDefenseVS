#ifndef MAP_H
#define MAP_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Square;
class Wall;
class Entrance;
class Exit;

class Map : public QObject
{
    Q_PROPERTY(int rowCount MEMBER rowCount NOTIFY rowCountChanged)
    Q_PROPERTY(int colCount MEMBER colCount NOTIFY colCountChanged)

    Q_OBJECT
public:
     Map(QObject *parent = 0);
     int rowCount;
     int colCount;
     int tileWidth;
     int tileHeight;

signals:
     void rowCountChanged(int newCount);
     void colCountChanged(int newCount);
     void tileHeightChanged(int newHeight);
     void tileWidthChanged(int newWidth);

     // signals sent to Game object which forwards to Board object
     void placeWall(int row, int col);
     void placeEntrance(int row, int col);
     void placeExit(int row, int col);
     void placeSquare(int row, int col);

public slots:
     void create_blank_map();
};

#endif // MAP_H
