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
}

void Path::clear_path()
{
    this->m_nodes.clear();

}

void Path::simplify()
{
    QList<QPair<int, int> > final_path;

    for (int i=0; i<m_nodes.count(); i++) {

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
            final_path << node;
            i = best_idx - 1;
        }
    }
    this->m_nodes.clear();
    this->m_nodes << final_path;

    qDebug() << "Simplified" << final_path.count();
}
