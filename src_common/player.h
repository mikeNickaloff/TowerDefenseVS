#ifndef PLAYER_H
#define PLAYER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QVariant>

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int money MEMBER m_money NOTIFY moneyChanged)
    Q_PROPERTY(int health MEMBER m_health NOTIFY healthChanged)
public:
    explicit Player(QObject *parent = 0, bool i_defender = true);
   int m_money;
    int m_health;
    bool isAttacker;
    bool isDefender;
signals:
    void moneyChanged(int newMoney);
    void healthChanged(int newHealth);
public slots:
};

#endif // PLAYER_H
