#include "path.h"
#include "tile.h"

Path::Path(QObject *parent) : QObject(parent)
{

}

void Path::append_node(int row, int col)
{
    this->m_nodes << qMakePair(row, col);
}

void Path::clear_path()
{
    this->m_nodes.clear();

}
