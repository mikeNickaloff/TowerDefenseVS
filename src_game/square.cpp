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

void Square::gotMouseClick()
{
emit this->signal_place_gun(m_tile->m_row, m_tile->m_col, 1);
}

void Square::setSelected(bool is_selected) {
    this->m_selected = is_selected;
    emit this->tileSelected(is_selected);
}
