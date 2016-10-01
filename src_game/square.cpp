#include "square.h"


#include "tile.h"
#include <QtDebug>
Square::Square(Tile *itile) : m_tile(itile)
{

}

Square::~Square()
{
    delete m_tile;
}

void Square::slot_erase()
{
    emit this->going_to_delete();
}

