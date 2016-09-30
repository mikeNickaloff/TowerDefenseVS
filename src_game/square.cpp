#include "square.h"


#include "tile.h"
#include <QtDebug>
Square::Square(Tile *itile) : m_tile(itile)
{

}

Square::~Square()
{
   // qDebug() << "Attempting to erase myself";
    emit going_to_delete();
}

