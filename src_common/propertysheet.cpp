#include "propertysheet.h"
#include "../src_game/gun.h"


/*int get_damage(int gun_type) { return m_damage.value(gun_type, 100); }
   int get_range(int gun_type) { return m_range.value(gun_type, 250); }
   int get_rate(int gun_type) { return m_rate.value(gun_type, 5); }
   int get_reload_time(int gun_type) { return m_reload_time.value(gun_type, 1500); }
   int get_splash_damage(int gun_type) { return m_splash_damage.value(gun_type, 75); }
   int get_splash_distance(int gun_type) { return m_splash_distance.value(gun_type, 35); }
   */
PropertySheet::PropertySheet(QObject *parent) : QObject(parent)
{
add_property(1, 250, 5, 1500, 100, 75, 35);
add_property(2, 300, 2, 100, 20, 35, 60);

}



void PropertySheet::add_property(int gun_type, int range, int bullet_rate, int reload_time, int damage, int splash_damage, int splash_distance)
{
 this->m_damage[gun_type] = damage;
    m_rate[gun_type] = bullet_rate;
    m_range[gun_type] = range;
    m_reload_time[gun_type] = reload_time;
    m_splash_damage[gun_type] = splash_damage;
    m_splash_distance[gun_type] = splash_distance;
}

void PropertySheet::apply_properties(Gun *i_gun)
{
    if (i_gun) {
        i_gun->m_damage = get_damage(i_gun->m_type);
        i_gun->m_rate = get_rate(i_gun->m_type);
        i_gun->m_range = get_range(i_gun->m_type);
        i_gun->m_reload_time = get_reload_time(i_gun->m_type);
        i_gun->m_splash_damage = get_splash_damage(i_gun->m_type);
        i_gun->m_splash_distance = get_splash_distance(i_gun->m_type);
    }
}
