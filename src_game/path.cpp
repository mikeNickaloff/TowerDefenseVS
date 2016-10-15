#include "path.h"
#include "tile.h"
#include "board.h"
#include <QtDebug>
Path::Path(QObject *parent, Board *i_board) : QObject(parent), m_board(i_board)
{

}

void Path::append_node(int row, int col)
{
    this->m_nodes << qMakePair(row, col);
    qDebug() << "Added Node  " << row << col << "total: " << m_nodes.count();
}

void Path::clear_path()
{
    this->m_nodes.clear();

}

void Path::simplify()
{
    QList<QPair<int, int> > final_path;
    if (m_nodes.count() > 5) {
        int i = 0;
        while (i < m_nodes.count()) {

            QPair<int, int> node = m_nodes.at(i);
            Tile* check_tile = m_board->find_tile(node.first, node.second);
            QList<Tile*> neighbors;

            int best_idx = -1;
            QPair<int, int> best_pair;
            neighbors << m_board->find_neighbors(check_tile);
            foreach (Tile* i_tile, neighbors) {
                QPair<int, int> pair = qMakePair(i_tile->m_row, i_tile->m_col);
                if ((m_nodes.indexOf(pair) > best_idx) && (m_nodes.indexOf(pair) > i)) { best_idx = m_nodes.indexOf(pair); best_pair = pair; }
            }
            if (best_idx == -1) {
                final_path << node;

            } else {
                final_path << node <<  best_pair;
                i = best_idx;
            }
            i++;
        }

        if ((final_path.count() < m_nodes.count()) && (final_path.count() > 0)) {
            this->m_nodes.clear();
            this->m_nodes << final_path;

            qDebug() << "Simplified" << final_path.count();
        }
    }
}
