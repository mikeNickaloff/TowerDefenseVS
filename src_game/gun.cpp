#include "gun.h"


#include "tile.h"
#include <QtDebug>
Gun::Gun(Tile *itile) : m_tile(itile)
{

}

Gun::~Gun()
{
    delete m_tile;
}

void Gun::slot_erase()
{
    emit this->going_to_delete();
}

void Gun::gotMouseClick()
{

}

