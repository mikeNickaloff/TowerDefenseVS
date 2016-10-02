#include "paththread.h"
#include "board.h"
#include "tile.h"
#include "entrance.h"
#include "exit.h"
#include "path.h"
#include <QThread>
#include <QtDebug>
#include <QLine>
#include <QDateTime>
PathThread::PathThread(QObject *parent, Board *i_board) : QThread(parent), m_board(i_board)
{

}
void PathThread::run() {


    qint64 start = QDateTime::currentMSecsSinceEpoch();
    int max_search = 5;
    qDebug() << m_board->find_tile(5,5)->m_walkable;
    Exit* ex = m_board->exits.first();
    for (int c=0; c<m_board->numColumns; c++) {
        for (int r=0; r<m_board->numRows; r++) {
            Tile* tmp_tile = this->m_board->find_tile(r, c);
            tmp_tile->distance_to_exit = distance_between(tmp_tile, ex->m_tile);
            tmp_tile->neighbors.clear();
            tmp_tile->neighbors << m_board->find_neighbors(tmp_tile);
        }
    }

    foreach (Entrance* en, m_board->entrances) {
        m_found_path = false;
        QList<Tile*> mainList;
        m_entrance = en;
        mainList << en->m_tile->neighbors;
        foreach (Tile* tmp_tile, mainList ) {
            qDebug() << mainList;
            QList<Tile*> previous;
            previous << tmp_tile;
            if ((tmp_tile != ex->m_tile) && (m_found_path == false)) {
                iterate_neighbors(tmp_tile, previous);
            }

        }

    } // end foreach entrance

    qint64 end = QDateTime::currentMSecsSinceEpoch();
    qDebug() << "Elapsed Time:" << (end - start) << "ms";
    exit();
}

void PathThread::iterate_neighbors(Tile *cur_tile, QList<Tile *> previous_tiles)
{
    // qDebug() << "Checking" << cur_tile <<  m_board->find_neighbors(cur_tile);;
    QList<Tile*> tmp_neighbors;
    tmp_neighbors << m_board->find_neighbors(cur_tile);
    int cheapest = 999;
    Exit* ex = m_board->exits.first();
    Tile* best_tile;
    foreach (Tile* u_tile, tmp_neighbors) {

        if (!previous_tiles.contains(u_tile)) {
            if (m_found_path == false) {
                if (u_tile->distance_to_exit < cheapest) {
                    cheapest = u_tile->distance_to_exit;
                    best_tile = u_tile;
                }
            }
        }
    }

    if (cheapest != 999) {
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
                        qDebug() << "DONE!"  << previous_tiles.count();

                        Path* path = m_board->find_path(m_entrance->m_tile->m_row, m_entrance->m_tile->m_col);
                        path->m_nodes.clear();
                        foreach (Tile* i_tile, new_previous) {
                            path->m_nodes << qMakePair(i_tile->m_row, i_tile->m_col);
                        }
                        m_found_path = true;
                    } else {
                        this->iterate_neighbors(u_tile, new_previous);
                    }
                }
            }
        }
    }
}

int PathThread::distance_between(Tile *tile1, Tile *tile2) {
    QLine line(tile1->m_col, tile1->m_row, tile2->m_col, tile2->m_row);
    return QPoint(line.p2() - line.p1()).manhattanLength();
}
