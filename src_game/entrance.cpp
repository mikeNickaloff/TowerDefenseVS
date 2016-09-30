#include <QtCore/QObject>
#include "entrance.h"
#include "tile.h"




Entrance::Entrance(Tile *itile, QObject* parent) : QObject(parent), m_tile(itile)
{

}
