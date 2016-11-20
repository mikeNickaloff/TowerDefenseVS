
#include <QObject>
#include <QQmlContext>

#include "game.h"
#include "../src_game/board.h"
#include "map.h"

#include "player.h"
#include "team.h"
#include "propertysheet.h"


Game::Game(QObject *parent) : QObject(parent)
{
    m_level = 1;
    p1 = new Player(this, true);
    p2 = new Player(this, false);
    m_money = 10000;
    p1->m_money = 10000;
    p2->m_money = 10000;
    p1->m_health = 10;
    p2->m_health = 10;
    this->m_props = new PropertySheet(this);
}
void Game::createBoard() {

    this->m_board = new Board(this, this);



}
void Game::createMap() {
    this->m_map = new Map(this);
   this->connect(m_map, SIGNAL(colCountChanged(int)), m_board, SLOT(changeColCount(int)));
    this->connect(m_map, SIGNAL(tileHeightChanged(int)), m_board, SLOT(tileHeightChanged(int)));
    this->connect(m_map, SIGNAL(tileWidthChanged(int)), m_board, SLOT(tileWidthChanged(int)));
    this->connect(m_map, SIGNAL(rowCountChanged(int)), m_board, SLOT(changeRowCount(int)));
    this->connect(m_map, SIGNAL(placeWall(int, int)), m_board, SLOT(placeWall(int,int)));
    this->connect(m_map, SIGNAL(placeEntrance(int, int)), m_board, SLOT(placeEntrance(int,int)));
    this->connect(m_map, SIGNAL(placeExit(int, int)), m_board, SLOT(placeExit(int,int)));
    this->connect(m_map, SIGNAL(placeSquare(int, int)), m_board, SLOT(placeSquare(int,int)));
    m_map->Map::create_blank_map();
}

void Game::award_defenders(int amount)
{
    if (p1->isDefender == true) {
        p1->m_money += amount;
        this->m_money = p1->m_money;
    } else {
        p2->m_money += amount;
    }
    emit this->moneyChanged(m_money);
}

void Game::award_attackers(int amount)
{
    if (p1->isAttacker == true) {
        p1->m_money += amount;

    } else {
        p2->m_money += amount;

    }
    emit this->moneyChanged(m_money);
}
