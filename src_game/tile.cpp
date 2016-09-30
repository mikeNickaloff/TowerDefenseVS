#include "tile.h"


Tile::Tile(QObject *parent, int irow, int icol, int iwidth, int iheight, bool i_buildable, bool i_walkable) : QObject(parent), m_row(irow), m_col(icol), m_width(iwidth), m_height(iheight), m_buildable(i_buildable), m_walkable(i_walkable)
{
m_x = icol * iwidth;
m_y = irow * iheight;
}

void Tile::setMyWidth(int new_width)
{
    this->m_width = new_width;
    emit this->myWidthChanged(new_width);
}
