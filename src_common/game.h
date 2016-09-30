#ifndef GAME_H
#define GAME_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlContext>



class Map;
class Square;
class Wall;
class Entrance;
class Exit;
class Wall;
class Board;
class Player;
class Team;
class Tile;
class Square;
class Game : public QObject
{
    Q_OBJECT
     Q_PROPERTY(Board* board MEMBER m_board NOTIFY boardChanged)
    Q_PROPERTY(int level MEMBER m_level NOTIFY levelChanged)
    Q_PROPERTY(int money MEMBER m_money NOTIFY moneyChanged)
public:
    Game(QObject *parent = 0, QQmlContext* i_context = 0);
    Board* m_board;
    Map* m_map;
    QQmlContext* m_context;
    int m_level;
    int m_money;


signals:
    void boardChanged(Board &new_board);
    void levelChanged(int newLevel);
    void moneyChanged(int newval);
public slots:
    // creates map object, too.
    void createBoard();

};

#endif // GAME_H
