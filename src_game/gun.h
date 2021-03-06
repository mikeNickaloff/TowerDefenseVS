#ifndef GUN_H
#define GUN_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QPoint>
#include <QtMath>
#include <QDateTime>
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

    // length of time it takes for a bullet to travel 10 pixels in MS
    int m_rate;

    int m_reload_time;

    int m_damage;

    int m_splash_distance;
    int m_splash_damage;

    double m_rotation;
   Entity* m_target_entity;
   int m_target_range;
   qint64 next_allowed_fire;
   qreal  angleTo(int cx, int cy, int ex, int ey) {
      qreal dy = ey - cy;
      qreal dx = ex - cx;
       qreal theta = qAtan2(dy, dx); // range (-PI, PI]
       theta *= 180 / (22 / 7); // rads to degs, range (-180, 180]
       return (360 + theta);
   }
   QPoint midpoint(QPoint pt1, QPoint pt2);

   QString serialize();
signals:
    void tileChanged(Tile* newTile);
    void going_to_delete();
    void tileSelected(bool isSelected);
    void typeChanged(int new_type);
    void rotationChanged(double newRot);

    void signal_fire(int endX, int endY, int gunType, int duration, int damage, int splash_distance, int splash_damage);
    void signal_show_upgradeStore(Gun* iGun);

    void callback_in_range(QPoint oldPos, QPoint newPos, Gun* i_me);
public slots:
    void slot_erase();
    void gotMouseClick();
    void setSelected(bool is_selected);
    void check_entity_within_range(QPoint oldPos, QPoint newPos, Entity* i_entity, bool callback_if_yes = true);
    void fire();
};
#endif // GUN_H
