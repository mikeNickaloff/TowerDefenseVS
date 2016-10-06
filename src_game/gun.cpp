#include "gun.h"


#include "tile.h"
#include "entity.h"
#include "path.h"
#include <QtDebug>
#include <QLine>
#include <QPoint>
Gun::Gun(Tile *itile) : m_tile(itile)
{
   m_range = 150;
   m_rotation = 0;
   m_target_entity = 0;
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

void Gun::check_entity_within_range(QPoint oldPos, QPoint newPos, Entity* i_entity)
{
    QPoint myPos = QPoint(m_tile->center());
    qreal newRot = m_rotation;
    int range = QPoint(newPos - myPos).manhattanLength();

    if (range <= m_range) {
        if (m_target_entity) {
            int oldRange = QPoint(QPoint(m_target_entity->m_x, m_target_entity->m_y) - myPos).manhattanLength();
            if ((i_entity->m_path->m_nodes.count() < m_target_entity->m_path->m_nodes.count()) || (oldRange > m_range) || (m_target_entity->completed == true)) {
                m_target_entity = i_entity;
                newRot = angleTo(QPointF(myPos).x(), QPointF(myPos).y(), QPointF(newPos).x(), QPointF(newPos).y());
               // emit this->rotationChanged(m_rotation);

            } else {
                newRot = angleTo(QPointF(myPos).x(), QPointF(myPos).y(), m_target_entity->m_x + (0.5 * m_target_entity->m_width) , m_target_entity->m_y + (0.5 * m_target_entity->m_height));
             //   emit this->rotationChanged(m_rotation);
            }
        } else {
            m_target_entity = i_entity;
           newRot = angleTo(QPointF(myPos).x(), QPointF(myPos).y(), QPointF(newPos).x(), QPointF(newPos).y());
           //emit this->rotationChanged(m_rotation);
        }

      //  qDebug() << "Enemy in range! Fire!";
    }
    if (qAbs((m_rotation + 360) - (newRot + 360)) > 180) {
        m_rotation = newRot - 360;
    } else {
        m_rotation = newRot;
    }
    emit this->rotationChanged(m_rotation);
}

