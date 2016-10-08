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
    m_rate = 10;
    m_reload_time = 1500;
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
            if (m_target_entity->completed == false) {
                int oldRange = QPoint(QPoint(m_target_entity->m_x, m_target_entity->m_y) - myPos).manhattanLength();
                if (oldRange > m_range) {
                    m_target_entity = i_entity;
                    newRot = angleTo(QPointF(myPos).x(), QPointF(myPos).y(), QPointF(newPos).x(), QPointF(newPos).y());
                } else {
                    if (i_entity->m_path->m_nodes.count() < m_target_entity->m_path->m_nodes.count()) {
                        int newRange = QPoint(QPoint(i_entity->m_x, i_entity->m_y) - myPos).manhattanLength();
                        if (newRange <= m_range) {
                            m_target_entity = i_entity;
                            newRot = angleTo(QPointF(myPos).x(), QPointF(myPos).y(), QPointF(newPos).x(), QPointF(newPos).y());
                        }
                        // emit this->rotationChanged(m_rotation);
                    } else {
                        if (m_target_entity->m_path->m_nodes.count() == 0) {
                            m_target_entity = i_entity;
                            newRot = angleTo(QPointF(myPos).x(), QPointF(myPos).y(), QPointF(newPos).x(), QPointF(newPos).y());
                        }
                    }
                }

            } else {


                m_target_entity = i_entity;
                newRot = angleTo(QPointF(myPos).x(), QPointF(myPos).y(), m_target_entity->m_x + (0.5 * m_target_entity->m_width) , m_target_entity->m_y + (0.5 * m_target_entity->m_height));

                //   emit this->rotationChanged(m_rotation);
            }
            if (i_entity == m_target_entity) {
                //m_target_entity = i_entity;
                newRot = angleTo(QPointF(myPos).x(), QPointF(myPos).y(), QPointF(newPos).x(), QPointF(newPos).y());
            }
        } else {
            m_target_entity = i_entity;
            newRot = angleTo(QPointF(myPos).x(), QPointF(myPos).y(), QPointF(newPos).x(), QPointF(newPos).y());
            //emit this->rotationChanged(m_rotation);
        }

        //  qDebug() << "Enemy in range! Fire!";

    }
    if (newRot != m_rotation) {
        if (qAbs((m_rotation + 360) - (newRot + 360)) > 180) {
            m_rotation = newRot - 360;
        } else {
            m_rotation = newRot;
        }
        emit this->rotationChanged(m_rotation);
    }
}

void Gun::fire()
{
    qint64 cur_time = QDateTime::currentMSecsSinceEpoch();
    if (cur_time >= this->next_allowed_fire) {
        if (m_target_entity) {
            if (m_target_entity->completed == false) {
                int distance = QPoint(m_target_entity->center() - m_tile->center()).manhattanLength();
                if (distance <= this->m_range) {
                    int particle_life = qRound(qRound((distance * 0.1) * this->m_rate) * 0.75);
                    // qDebug() << "Firing at " << m_target_entity->center().x() << m_target_entity->center().y() << particle_life;
                    emit this->signal_fire(m_target_entity->center().x(), m_target_entity->center().y(), this->m_type, particle_life);
                    this->next_allowed_fire = cur_time + this->m_reload_time;
                }
            }
        }
    }
}

