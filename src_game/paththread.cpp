#include "paththread.h"
#include "board.h"
#include "tile.h"
#include "entrance.h"
#include "exit.h"
#include "path.h"
#include "square.h"
#include "entity.h"
#include "enemy.h"
#include "../src_common/astarpath.h"
#include <QThread>
#include <QtDebug>
#include <QLine>
#include <QDateTime>
#include <QMutex>
PathThread::PathThread(QObject *parent, Board *i_board) : QThread(parent), m_board(i_board)
{

}
void PathThread::run() {

    QMutex mutex;
   mutex.lock();
    /*High = 10;
    Low = 3;
    qsrand(QDateTime::currentMSecsSinceEpoch());
    random_num = (qrand() % 3)+1;

    qDebug() << "Random Num is" << random_num;*/
    m_blocked_path = false;
    start_time = QDateTime::currentMSecsSinceEpoch();
    int max_search = 5;
    //qDebug() << m_board->find_tile(5,5)->m_walkable;
    Exit* ex = m_board->exits.first();
    for (int c=0; c<m_board->numColumns; c++) {
        for (int r=0; r<m_board->numRows; r++) {
            Tile* tmp_tile = this->m_board->find_tile(r, c);
            tmp_tile->distance_to_exit = distance_between(tmp_tile, ex->m_tile);
            tmp_tile->neighbors.clear();
            tmp_tile->neighbors << m_board->find_neighbors(tmp_tile);
        }
    }
    //QThread::msleep(100);
    foreach (Entrance* en, m_board->entrances) {
        m_found_path = false;
        QList<Tile*> mainList;
        m_entrance = en;

        /* start of AStar */

        Tile* entile = en->m_tile;
     //   Path* path = m_board->find_path(entile->m_row, entile->m_col);
        QList<Tile*> rez;

        m_blocked_path = false;
        rez << m_board->new_star->find_path(entile, ex->m_tile);
        //m_found_path = true;
        if (rez.count() < 3) { m_blocked_path = true; } else { m_blocked_path = false; }
        if (!m_blocked_path) {
            m_board->find_path(entile->m_row, entile->m_col)->clear_path();
          //  qSort(rez.end(), rez.begin());
            //path->m_nodes.clear();
            foreach (Tile* i_tile, rez) {
                m_board->find_path(entile->m_row, entile->m_col)->append_node(i_tile->m_row, i_tile->m_col);

            }
        }
        /* end of AStar */



      /* mainList << en->m_tile->neighbors;
        if (!m_blocked_path) {
            foreach (Tile* tmp_tile, mainList ) {
                //   qDebug() << mainList;
                QList<Tile*> previous;
                previous << tmp_tile;
                if ((m_board->find_path(m_entrance->m_tile->m_row, m_entrance->m_tile->m_col)->m_nodes.count() == 0) || ((m_board->find_path(m_entrance->m_tile->m_row, m_entrance->m_tile->m_col)->m_nodes.count() > 2) && (m_board->find_path(m_entrance->m_tile->m_row, m_entrance->m_tile->m_col)->m_nodes.contains(m_board->triggering_node)))) {
                    if ((tmp_tile != ex->m_tile) && (m_found_path == false)) {
                        // QThread::msleep(13);
                        iterate_neighbors(tmp_tile, previous, m_entrance->m_tile);

                    }

                }
            }
        }
*/
    } // end foreach entrance


    foreach (QObject* obj, m_board->db_entities.values()) {
        Enemy* enemy = qobject_cast<Enemy*>(obj);
        if (!enemy)
            continue;

        m_found_path = false;
        if (enemy->m_entity) {
            Entity* en = enemy->m_entity;
            QList<Tile*> mainList;
            m_entity = en;
            // qDebug() << "Found entity" << en;
            if ((m_entity->m_path->m_nodes.count() > 2) && (m_entity->m_path->m_nodes.contains(m_board->triggering_node))) {

                QList<Tile*> rez2;

                m_blocked_path = false;
                rez2 << m_board->new_star->find_path(m_board->find_tile(m_entity->m_path->m_nodes.first().first, m_entity->m_path->m_nodes.first().second), ex->m_tile);
                if (rez2.count() < 3) { m_blocked_path = true; } else { m_blocked_path = false; }
                if (!m_blocked_path) {
                    int oldPathSize = m_entity->m_path->m_nodes.count();
                    while (rez2.count() > 0) {
                        Tile* t_tile = rez2.takeFirst();
                    m_entity->m_path->append_node(t_tile->m_row, t_tile->m_col);

                }
                   for (int a=0; a<oldPathSize; a++) {
                       m_entity->m_path->m_nodes.takeFirst();
                   }
                }

                //     qDebug() << "Found path" << m_entity->m_path->m_nodes;
              /*  mainList << m_board->find_tile(m_entity->m_path->m_nodes.first().first, m_entity->m_path->m_nodes.first().second);

                if (!m_blocked_path) {
                    foreach (Tile* u_tmp_tile, mainList ) {
                        //   qDebug() << mainList;
                        Tile* tmp_tile = u_tmp_tile;
                        QList<Tile*> previous;


                        previous << tmp_tile;

                        if ((tmp_tile != ex->m_tile) && (m_found_path == false)) {
                            // QThread::msleep(13);
                            //  qDebug() << "Iterating";
                            iterate_neighbors(tmp_tile, previous, tmp_tile);

                        }

                    }
                    Tile* atile = mainList.first();
                    if (atile) {
                        //qDebug() << "Looking for path";
                        Path* path = m_board->find_path(atile->m_row, atile->m_col);
                        if (path) {
                            //   qDebug() << "Clearing Path";
                            // m_entity->m_path->clear_path();
                            //     qDebug() << "Setting nodes";
                            for (int a=0; a<path->m_nodes.count(); a++) {
                                QPair<int, int> pair = path->m_nodes.at(a);
                                m_entity->m_path->m_nodes.insert(a, pair);
                            }
                            for (int a=(path->m_nodes.count() - 1); a<(m_entity->m_path->m_nodes.count() + 0); a++) {
                                if (m_entity->m_path->m_nodes.count() > 0) {
                                    m_entity->m_path->m_nodes.removeLast();
                                }
                            }
                              // m_entity->m_path->simplify();
                            //m_entity->m_path->m_nodes << path->m_nodes;
                        }
                    }


                } */

            }
        }
    }


    if (m_blocked_path == true) {
        emit this->place_last_gun(false);


    } else {
        emit this->place_last_gun(true);
    }

    mutex.unlock();
    qint64 end_time = QDateTime::currentMSecsSinceEpoch();
    qDebug() << "Elapsed Time:" << (end_time - start_time) << "ms";
    exit();
}

void PathThread::iterate_neighbors(Tile *cur_tile, QList<Tile *> i_previous_tiles, Tile *start_tile)
{
    // qDebug() << "Checking" << cur_tile <<  m_board->find_neighbors(cur_tile);;
    QList<Tile*> previous_tiles;
    if ((i_previous_tiles.count()  % 25) == 0) {
        previous_tiles << compress_list(i_previous_tiles);
    } else {
        previous_tiles << i_previous_tiles;
    }
    QList<Tile*> tmp_neighbors;
    tmp_neighbors << m_board->find_neighbors(cur_tile);
    int cheapest = 99999;
    Exit* ex = m_board->exits.first();
    Tile* best_tile;
    qint64 end_time = QDateTime::currentMSecsSinceEpoch();
    if ((end_time - start_time) < 2000) {
        foreach (Tile* u_tile, tmp_neighbors) {

            if (!previous_tiles.contains(u_tile)) {
                if (m_found_path == false) {
                    if (u_tile->distance_to_exit < cheapest) {
                        cheapest = u_tile->distance_to_exit;
                        best_tile = u_tile;
                        // Square* sq = m_board->find_square(u_tile->m_row, u_tile->m_col);

                    }
                }
            }
        }

        if ((cheapest != 99999) && (m_found_path == false)) {
            QList<Tile*> new_neighbors;


            new_neighbors << best_tile;


            foreach (Tile* u_tile, tmp_neighbors) {
                if (!previous_tiles.contains(u_tile)) {
                    if (u_tile != best_tile) {
                        new_neighbors << u_tile;
                    }
                }
            }

            foreach (Tile* u_tile, new_neighbors) {
                if (m_found_path == false) {
                    if (!previous_tiles.contains(u_tile)) {
                        QList<Tile*> new_previous;
                        new_previous << previous_tiles;
                        new_previous << u_tile;
                        if (u_tile == ex->m_tile) {
                            //   qDebug() << "DONE!"  << previous_tiles.count();

                            Path* path = m_board->find_path(start_tile->m_row, start_tile->m_col);
                            if (path) {
                                path->m_nodes.clear();
                                foreach (Tile* i_tile, new_previous) {
                                    path->m_nodes << qMakePair(i_tile->m_row, i_tile->m_col);
                                }
                                //    path->simplify();
                                m_found_path = true;
                            }
                        } else {
                            this->iterate_neighbors(u_tile, new_previous, start_tile);
                        }
                    }
                }
            }
        }
    } else {
        qDebug() << "No valid paths found!!";
        m_blocked_path = true;
        m_found_path = true;
    }
}

QList<Tile *> PathThread::compress_list(QList<Tile *> inp_list)
{

    QList<Tile*> final_path;
    return inp_list;
    if ((inp_list.count() > 15)) {
        for (int i=0; i<inp_list.count(); i++) {
            if (inp_list.count() > i) {
                Tile* check_tile = inp_list.at(i);
                //Tile* check_tile = m_board->find_tile(node.first, node.second);
                QList<Tile*> neighbors;

                int best_idx = -1;
                Tile* best_tile;
                neighbors << m_board->find_neighbors(check_tile);
                Tile* best_neighbor;
                int best_neighbor_index;
                Tile* best_p_tile;
                foreach (Tile* i_tile, neighbors) {


                    // foreach (Tile* i_tile, m_board->find_neighbors(q_tile)) {
                    if (i_tile != check_tile) {
                        if ((inp_list.indexOf(i_tile) > best_idx) && (inp_list.indexOf(i_tile) > i)) { best_idx = inp_list.indexOf(i_tile); best_tile = i_tile; /*best_neighbor = q_tile; best_neighbor_index = inp_list.indexOf(q_tile); */  }
                    }
                    //  }
                }

                if (best_idx == -1) {
                    final_path << check_tile;
                } else {
                    final_path << check_tile << best_tile;
                    i = best_idx - 1;

                }
            }
        }
        //this->m_nodes.clear();
        //this->m_nodes << final_path;

        //qDebug() << "Simplified" << final_path.count();

    } else {
        final_path << inp_list;
        return final_path;
    }
    if ((final_path.count() > 0) && (final_path.count() < inp_list.count())) {
        return final_path;
    }
    return inp_list;
}

int PathThread::distance_between(Tile *tile1, Tile *tile2) {
    QLine line(tile1->m_x, tile1->m_y, tile2->m_x, tile2->m_y);
    return QPoint(line.p2() - line.p1()).manhattanLength();
}


