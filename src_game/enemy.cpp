
#include "enemy.h"
#include "entity.h"
#include "board.h"

Enemy::Enemy(QObject *parent, Entity *i_entity, Board *i_board) : QObject(parent), m_entity(i_entity), m_board(i_board)
{

}
