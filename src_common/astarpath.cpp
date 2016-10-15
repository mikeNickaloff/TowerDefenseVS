#include "astarpath.h"
#include "../src_game/board.h"
#include "../src_game/tile.h"
#include "../src_game/entrance.h"
#include "../src_game/exit.h"
#include "../src_game/path.h"
#include "../src_game/square.h"
#include "../src_game/entity.h"
#include "../src_game/enemy.h"
#include "../src_game/wall.h"
#include "../src_game/gun.h"
#include <QtDebug>
#include <QObject>
AStarPath::AStarPath(QObject *parent, Board *i_board) : QObject(parent), m_board(i_board)
{

}

QList<Tile*> AStarPath::find_path(Tile *i_start, Tile *i_end)
{
    QList<Tile*> rv;
    rv << i_start;
    openSet.clear();
    closedSet.clear();
    openSet.append(i_start);
    cameFrom.clear();
    foreach (int idx, m_board->db_tiles.keys()) {
        Tile* i_tile = m_board->find_tile(m_board->getRow(idx), m_board->getCol(idx));
            //gScore[i_tile] = QPoint(QPoint(i_tile->m_col, i_tile->m_row) - QPoint(i_start->m_col, i_start->m_row)).manhattanLength();
        gScore[i_tile] = 99999999;
            fScore[i_tile] = 999999;

    }
    fScore.insert(i_start, QPoint(QPoint(i_end->m_col, i_end->m_row) - QPoint(i_start->m_col, i_start->m_row)).manhattanLength());
    gScore.insert(i_start, 0);
    while (openSet.count() > 0) {
        Tile* best_tile = 0;
        int best_fscore = 9999999;
        foreach (Tile* u_tile, openSet) {
            if (fScore.value(u_tile, 99999) <= best_fscore) {
                best_tile = u_tile;
                best_fscore = fScore.value(u_tile, 99999);
            }
        }
        if (best_tile) {
            if (best_tile == i_end) {
              //  cameFrom.insert(i_end, best_tile);
                rv << reconstruct_path(best_tile);
                return rv;
            }

            openSet.removeAll(best_tile);
            closedSet.append(best_tile);
            foreach (Tile* neighbor, m_board->find_neighbors(best_tile)) {
                if (closedSet.contains(neighbor)) {
                    continue;
                }

                int tentative_gScore = gScore.value(best_tile) + QPoint(QPoint(best_tile->m_col, best_tile->m_row) - QPoint(neighbor->m_col, neighbor->m_row)).manhattanLength();
                if (!openSet.contains(neighbor)) {
                    openSet.append(neighbor);

                    qDebug() << "open" << openSet;
                    qDebug() << "---";
                    qDebug() << "closed" << closedSet;
                    qDebug() << "--------------------";
                } else {
                    if (tentative_gScore >= gScore.value(neighbor)) {
                     continue;
                    }
                }
                cameFrom.insert(neighbor, best_tile);
                gScore.insert(neighbor, tentative_gScore);
                fScore.insert(neighbor, gScore.value(neighbor) + QPoint(QPoint(neighbor->m_col, neighbor->m_row) - QPoint(i_end->m_col, i_end->m_row)).manhattanLength());
            }


        }
    }
    qDebug() << "AStar Failure";
    return rv;

}

QList<Tile *> AStarPath::reconstruct_path(Tile *i_end)
{
    QList<Tile*> rv;
   // rv << i_end;
    Tile* current = i_end;
    while (cameFrom.keys().contains(current)) {
        current = cameFrom.value(current);
        if (!m_board->find_entrance(current->m_row, current->m_col)) {
            rv.prepend(current);
        }
    }
    qDebug() << "Reconstructed:" << rv;
   // rv.takeFirst();
    //rv.takeFirst();
    return rv;
}











 /* *
   *
   *
   *
   *
  function A*(start, goal)
      // The set of nodes already evaluated.
      closedSet := {}
      // The set of currently discovered nodes still to be evaluated.
      // Initially, only the start node is known.
      openSet := {start}
      // For each node, which node it can most efficiently be reached from.
      // If a node can be reached from many nodes, cameFrom will eventually contain the
      // most efficient previous step.
      cameFrom := the empty map

      // For each node, the cost of getting from the start node to that node.
      gScore := map with default value of Infinity
      // The cost of going from start to start is zero.
      gScore[start] := 0
      // For each node, the total cost of getting from the start node to the goal
      // by passing by that node. That value is partly known, partly heuristic.
      fScore := map with default value of Infinity
      // For the first node, that value is completely heuristic.
      fScore[start] := heuristic_cost_estimate(start, goal)

      while openSet is not empty
          current := the node in openSet having the lowest fScore[] value
          if current = goal
              return reconstruct_path(cameFrom, current)

          openSet.Remove(current)
          closedSet.Add(current)
          for each neighbor of current
              if neighbor in closedSet
                  continue		// Ignore the neighbor which is already evaluated.
              // The distance from start to a neighbor
              tentative_gScore := gScore[current] + dist_between(current, neighbor)
              if neighbor not in openSet	// Discover a new node
                  openSet.Add(neighbor)
              else if tentative_gScore >= gScore[neighbor]
                  continue		// This is not a better path.

              // This path is the best until now. Record it!
              cameFrom[neighbor] := current
              gScore[neighbor] := tentative_gScore
              fScore[neighbor] := gScore[neighbor] + heuristic_cost_estimate(neighbor, goal)

      return failure

  function reconstruct_path(cameFrom, current)
      total_path := [current]
      while current in cameFrom.Keys:
          current := cameFrom[current]
          total_path.append(current)
      return total_path

*/
