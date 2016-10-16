#ifndef GAME_H
#define GAME_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlContext>



class Map;

class Board;
class Team;
class Player;

class PropertySheet;
class Game : public QObject
{
    Q_OBJECT
     Q_PROPERTY(Board* board MEMBER m_board NOTIFY boardChanged)
    Q_PROPERTY(int level MEMBER m_level NOTIFY levelChanged)
    Q_PROPERTY(int money MEMBER m_money NOTIFY moneyChanged)
public:
    Game(QObject *parent = 0);
    Board* m_board;
    Map* m_map;
    QQmlContext* m_context;
    int m_level;
    int m_money;
    Player* p1;
    Player* p2;
    PropertySheet* m_props;

signals:
    void boardChanged(Board &new_board);
    void levelChanged(int newLevel);
    void moneyChanged(int newval);
public slots:
    // creates map object, too.
    void createBoard();
    void createMap();
    void award_defenders(int amount);
    void award_attackers(int amount);

};

#endif // GAME_H
