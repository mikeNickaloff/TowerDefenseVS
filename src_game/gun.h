#ifndef GUN_H
#define GUN_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QPoint>
#include <QtMath>
class Tile;
class Entity;
class Path;
class Gun : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Tile* tile MEMBER m_tile NOTIFY tileChanged)
    Q_PROPERTY(int type MEMBER m_type NOTIFY typeChanged)
    Q_PROPERTY(double rotation MEMBER m_rotation NOTIFY rotationChanged)
public:
    Gun(Tile* itile = 0);
    ~Gun();
    Tile* m_tile;  // pointer to Tile object
    bool m_selected;
    int m_type;
    int m_range;
    double m_rotation;
   Entity* m_target_entity;
   int m_target_range;
   qreal  angleTo(int cx, int cy, int ex, int ey) {
      qreal dy = ey - cy;
      qreal dx = ex - cx;
       qreal theta = qAtan2(dy, dx); // range (-PI, PI]
       theta *= 180 / (22 / 7); // rads to degs, range (-180, 180]
       return (360 + theta);
   }
signals:
    void tileChanged(Tile* newTile);
    void going_to_delete();
    void tileSelected(bool isSelected);
    void typeChanged(int new_type);
    void rotationChanged(double newRot);

public slots:
    void slot_erase();
    void gotMouseClick();
    void check_entity_within_range(QPoint oldPos, QPoint newPos, Entity* i_entity);
};
#endif // GUN_H
