#ifndef GUN_H
#define GUN_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
class Tile;
class Gun : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Tile* tile MEMBER m_tile NOTIFY tileChanged)
    Q_PROPERTY(int type MEMBER m_type NOTIFY typeChanged)
public:
    Gun(Tile* itile = 0);
    ~Gun();
    Tile* m_tile;  // pointer to Tile object
    bool m_selected;
    int m_type;
signals:
    void tileChanged(Tile* newTile);
    void going_to_delete();
    void tileSelected(bool isSelected);
    void typeChanged(int new_type);

public slots:
    void slot_erase();
    void gotMouseClick();
};
#endif // GUN_H
