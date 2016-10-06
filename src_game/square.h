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
    bool m_selected;
signals:
    void tileChanged(Tile* newTile);
    void going_to_delete();
    void tileSelected(bool isSelected);
    void signal_place_gun(int row, int col, int gun_type);
    void signal_show_gunStore(bool is_shown);

public slots:
    void slot_erase();
    void gotMouseClick();
    void setSelected(bool is_selected);
};

#endif // SQUARE_H
