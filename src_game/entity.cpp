
#include "entity.h"
#include "board.h"
#include "square.h"
#include "tile.h"
#include "path.h"
#include <QPoint>
#include <QtDebug>
#include <QTimer>
#include <QRect>
Entity::Entity(QObject *parent, Board *i_board) : QObject(parent), m_board(i_board)
{
completed = false;
_realpos = QPoint(0,0);
}

void Entity::next_path_tile()
{
    if (m_path->m_nodes.count() > 0) {
        QPair<int, int> pair = m_path->m_nodes.takeFirst();
        Tile* tile = m_board->find_tile(pair.first, pair.second);
        if (m_board->find_exit(pair.first, pair.second)) {
            completed = true;
            emit this->completed_path(m_entityIndex);
          //  _realpos = QPoint(9999,9999);
        } else {
            QPoint oldPos = QPoint(m_x, m_y);
            QPoint oldCenter = center();
            emit this->rotationChanged(90 + angleTo(oldCenter.x(), oldCenter.y(), tile->center().x(), tile->center().y()));
            set_x(tile->m_x);
            set_y(tile->m_y);
            if (tile->m_buildable) { emit this->opacityChanged(1.0); m_opacity = 1.0; } else { emit this->opacityChanged(0.1); m_opacity = 0.1;}
            QPoint newPos = QPoint(m_x, m_y);
            QPoint newCenter = center();
            emit this->callout_position(oldPos, newPos);
            QPoint delta = QPoint(newCenter - oldCenter);
            delta.setX(delta.x() * 0.5);
            delta.setY(delta.y() * 0.5);
            _realpos = QPoint(oldCenter + delta);
            // qDebug() << "Changing x to " << tile->m_x << "and y to: " << tile->m_y;
            QTimer::singleShot(m_speed, this, SLOT(next_path_tile()));
        }
    } else {
        emit this->killed(m_entityIndex);
        this->completed = true;
    }
}
QPoint Entity::center()
{
    QRect rect(m_x, m_y, m_width, m_height);
    return rect.center();
}

QPoint Entity::realpos()
{
    return _realpos;
}
