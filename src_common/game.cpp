#include "game.h"
#include "../src_game/header.h"
#include "map.h"

#include <QObject>
#include <QQmlContext>
#include "player.h"
#include "team.h"


Game::Game(QObject *parent, QQmlContext *i_context) : QObject(parent), m_context(i_context)
{
    m_level = 1;
}
void Game::createBoard() {
    this->m_map = new Map(this);
    this->m_board = new Board(this, this);
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
