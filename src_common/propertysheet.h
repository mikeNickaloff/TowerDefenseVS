#ifndef PROPERTYSHEET_H
#define PROPERTYSHEET_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QHash>

class Gun;
class Enemy;
class PropertySheet : public QObject
{
    Q_OBJECT
public:
    explicit PropertySheet(QObject *parent = 0);

    // <gun type,  range value>
    QHash<int, int> m_range;

    //length of time [in millisecs] for bullet to travel 10 pixels
    QHash<int, int> m_rate;

    // time in MS delay between shots
    QHash<int, int> m_reload_time;



   QHash<int, int> m_damage;

   QHash<int, int> m_splash_damage;

   QHash<int, int> m_splash_distance;

   int get_damage(int gun_type) { return m_damage.value(gun_type, 100); }
   int get_range(int gun_type) { return m_range.value(gun_type, 250); }
   int get_rate(int gun_type) { return m_rate.value(gun_type, 5); }
   int get_reload_time(int gun_type) { return m_reload_time.value(gun_type, 1500); }
   int get_splash_damage(int gun_type) { return m_splash_damage.value(gun_type, 75); }
   int get_splash_distance(int gun_type) { return m_splash_distance.value(gun_type, 35); }

   QHash<int, int> enemy_speed;
   QHash<int, int> enemy_health;
   QHash<int, int> enemy_cost;

   int get_enemy_speed(int enemy_type) { return enemy_speed.value(enemy_type, 500); }
   int get_enemy_health(int enemy_type) { return enemy_health.value(enemy_type, 300); }
   int get_enemy_cost(int enemy_type) { return enemy_cost.value(enemy_type, 50); }

signals:

public slots:
   void add_property(int gun_type, int range, int bullet_rate, int reload_time, int damage, int splash_damage, int splash_distance);
   void add_property(int enemy_type, int enemy_speed, int enemy_health, int enemy_cost);
   void apply_properties(Gun* i_gun);
   void apply_properties(Enemy* i_enemy);

};

#endif // PROPERTYSHEET_H
