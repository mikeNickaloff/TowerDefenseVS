
#include "entity.h"
#include "board.h"
#include "square.h"
#include "tile.h"
#include "path.h"
#include <QPoint>
#include <QtDebug>
#include <QTimer>
Entity::Entity(QObject *parent, Board *i_board) : QObject(parent), m_board(i_board)
{

}

void Entity::next_path_tile()
{
    if (m_path->m_nodes.count() > 0) {
        QPair<int, int> pair = m_path->m_nodes.takeFirst();
        Tile* tile = m_board->find_tile(pair.first, pair.second);
        if (m_board->find_exit(pair.first, pair.second)) {
            emit this->completed_path(m_entityIndex);
        } else {
            set_x(tile->m_x);
            set_y(tile->m_y);
            // qDebug() << "Changing x to " << tile->m_x << "and y to: " << tile->m_y;
            QTimer::singleShot(m_speed, this, SLOT(next_path_tile()));
        }
    } else {
        emit this->completed_path(m_entityIndex);
    }
}
