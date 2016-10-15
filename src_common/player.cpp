#include "player.h"

Player::Player(QObject *parent, bool i_defender) : QObject(parent)
{
this->isDefender = i_defender;
    this->isAttacker = !i_defender;
}
