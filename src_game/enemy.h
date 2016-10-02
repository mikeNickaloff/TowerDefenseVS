#ifndef ENEMY_H
#define ENEMY_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
class Entity;
class Board;
class Enemy : public QObject
{
    Q_OBJECT
     Q_PROPERTY(int type MEMBER m_type NOTIFY typeChanged)
    Q_PROPERTY(int health MEMBER m_health NOTIFY healthChanged)
    Q_PROPERTY(int speed MEMBER m_speed NOTIFY speedChanged)
    Q_PROPERTY(Entity* entity MEMBER m_entity NOTIFY entityChanged)
public:
    explicit Enemy(QObject* parent = 0, Entity* i_entity = 0, Board* i_board = 0);
    Entity* m_entity;
    Board* m_board;
    int m_type;
    int m_health;

    // number of MS it takes to travel one tile
    int m_speed;
signals:

    void typeChanged(int new_type);
    void healthChanged(int new_health);
    void speedChanged(int new_speed);
    void entityChanged(Entity* new_entity);
public slots:
};

#endif // ENEMY_H
