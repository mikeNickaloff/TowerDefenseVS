#include "board.h"
#include "enemy.h"
#include "entity.h"
#include "entrance.h"
#include "exit.h"
#include "projectile.h"
#include "square.h"
#include "tile.h"
#include "tower.h"
#include "wall.h"

#include "path.h"
#include "../src_common/game.h"
#include "paththread.h"
#include <QtDebug>
#include <QTimer>
#include <QPointer>
#include <QVariant>
#include <QThread>
Board::Board(QObject *parent, Game *i_game) : QObject(parent), m_game(i_game)
{
    numRows = 50;
    numColumns = 50;
    QTimer::singleShot(5000, this, SLOT(populate_entry_paths()));
    QTimer::singleShot(10000, this, SLOT(spawn_random_enemy()));
    entrance_index = 0;

}
void Board::changeRowCount(int newCount) {
    numRows = newCount;
    emit this->signal_update_pathing_grid(numRows, numColumns);
}
void Board::changeColCount(int newCount) {
    numColumns = newCount;
    emit this->signal_update_pathing_grid(numRows, numColumns);
}
void Board::eraseTile(int row, int col) {
    emit this->signal_tile_erased(row, col);
    QPointer<QObject> obj = db_tiles.value(getIndex(row, col));
    db_tiles.remove(getIndex(row, col));
    if (obj)
        delete obj;


}

void Board::tileHeightChanged(int newHeight)
{
    tileHeight = newHeight;
}

void Board::tileWidthChanged(int newWidth)
{
    tileWidth = newWidth;
}

void Board::placeWall(int row, int col) {
    eraseTile(row, col);
    this->new_wall = new Wall(create_tile(row, col, tileWidth, tileHeight, false, false));
    this->db_tiles.insert(getIndex(row, col), new_wall);
    emit this->signal_wall_added(new_wall);
    emit this->signal_pathing_set_walkable(row, col, false);
}

void Board::placeSquare(int row, int col) {
    this->new_square = new Square(create_tile(row, col, tileWidth, tileHeight, true, true));
    db_tiles.insert(getIndex(row, col), new_square);
    //  qDebug() << "Board: Got word to create new Square" << new_square;
    emit this->signal_square_added(new_square);
    emit this->signal_pathing_set_walkable(row, col, true);

}

void Board::placeEntrance(int row, int col) {
    this->new_entrance = new Entrance(create_tile(row, col, tileWidth, tileHeight, false, true));
    db_tiles.insert(getIndex(row, col), new_entrance);
    emit this->signal_entrance_added(new_entrance);
    emit this->signal_pathing_set_walkable(row, col, true);
}

void Board::placeExit(int row, int col) {
    this->new_exit = new Exit(create_tile(row, col, tileWidth, tileHeight, false, true));
    db_tiles.insert(getIndex(row, col), new_exit);
    emit this->signal_exit_added(new_exit);
    emit this->signal_pathing_set_walkable(row, col, true);
}

void Board::clear_path_data(int from_row, int from_col)
{
    Path* path = find_path(from_row, from_col);
    if (path) {
        path->clear_path();
    }
}

void Board::clear_target_path_data(Enemy *targetObject)
{

}

void Board::add_path_data(int r1, int c1, int from_row, int from_col)
{

    Path* path = find_path(from_row, from_col);
    if (path) {
        path->append_node(r1, c1);
    } else {
        new_path = new Path(this);
        this->db_paths.insert(getIndex(from_row, from_col), new_path);
        add_path_data(r1, c1, from_row, from_col);
    }
    qDebug() << "Added path Node" << c1 << r1;
}

void Board::add_target_path_data(Enemy *targetObject, int c1, int r1)
{

}

void Board::update_walkable_states()
{
    /*  QHash<int, QObject*>::const_iterator o;
    o = this->db_tiles.constBegin();
    while (o != db_tiles.constEnd()) {

        Tile* tile = find_tile(getRow(o.key()), getCol(o.key()));
        if (tile) {
            emit this->signal_pathing_set_walkable(tile->m_row, tile->m_col, tile->m_walkable);
        }
        o++;
    } */

}

void Board::populate_entry_paths()
{

    exits.clear();
    entrances.clear();
    QHash<int, QObject*>::const_iterator i = this->db_tiles.constBegin();
    while (i != db_tiles.constEnd()) {
        Exit* ex = qobject_cast<Exit*>(i.value());
        if (ex) {
            exits << ex;
        }
        i++;
    }
    qDebug() << "exit count is" << exits.count();
    i = db_tiles.constBegin();
    while (i != db_tiles.constEnd()) {
        //int idx = i.key();
        Entrance* en = qobject_cast<Entrance*>(i.value());
        if (en) {
            entrances << en;
        }


        i++;
    }
    foreach (Entrance* en, entrances) {
        Path* path = find_path(en->m_tile->m_row, en->m_tile->m_col);
        path->clear_path();
    }
    qDebug() << "Entrance count: " << entrances.count();
    this->m_paththread = new PathThread(this, this);
    m_paththread->start();
    entrance_index = 0;
    exit_index = -1;
    //next_exit();

}

void Board::next_exit()
{
    qDebug() << "GOing to next exit";
    exit_index++;
    if (exit_index >= exits.count()) {
        next_entrance();
    } else {
        Exit* ex = exits.at(exit_index);
        Entrance* en = entrances.at(entrance_index);
        emit this->signal_update_pathing_grid(numRows,numColumns);
        this->update_walkable_states();
        emit this->signal_get_shortest_target_path(en->m_tile->m_col, en->m_tile->m_row, ex->m_tile->m_col, ex->m_tile->m_row, 0);
    }
}

void Board::next_entrance()
{
    qDebug() << "Going to next entrance";
    exit_index = -1;
    entrance_index++;
    if (entrance_index >= entrances.count()) {
        // done
    } else {
        next_exit();
    }
}

void Board::changed_xy_board_translation(int new_x, int new_y)
{
    emit this->signal_update_xy_translation(new_x, new_y);
}

void Board::create_enemy(Tile *i_tile, int height, int width, int speed, int health, int i_type)
{
    new_enemy = new Enemy(this, create_entity(i_tile->m_x, i_tile->m_y, height, width), this);
    int lastEntity = 0;
    QList<int> list;
    list << this->db_entities.keys();
    if (list.count() > 0) {
        qSort(list.begin(), list.end());
        lastEntity = list.last();
        lastEntity++;
    }
    this->db_entities[lastEntity] = new_enemy;
    new_enemy->m_speed = speed;
    new_enemy->m_health = health;
    new_enemy->m_type = i_type;
    new_path = new Path(this);
    new_path->m_nodes << this->db_paths.value(getIndex(i_tile->m_row, i_tile->m_col))->m_nodes;
    new_enemy->m_entity->m_path = new_path;
    new_enemy->m_entity->m_speed = speed;
    //new_enemy->m_entity->next_path_tile();
   emit this->signal_enemy_added(new_enemy);
    QTimer::singleShot(speed, new_enemy->m_entity, SLOT(next_path_tile()));
}

void Board::spawn_random_enemy()
{
    entrance_index++;
    if (entrance_index >= entrances.count()) { entrance_index = 0; }
    this->create_enemy(this->entrances.at(entrance_index)->m_tile, this->tileHeight, this->tileWidth, 1000, 1000, 1);
       QTimer::singleShot(1000, this, SLOT(spawn_random_enemy()));
}
















/*   --------------------------
 *
 *        Typed Responses
 *
 *   ------------------------- */


int Board::getIndex(int row, int col)
{
    return (row * 1000) + col;
}

int Board::getRow(int index)
{
    return (int) (index / 1000);
}

int Board::getCol(int index)
{
    return (int)(index - (getRow(index) * 1000));
}

Tile *Board::create_tile(int row, int col, int i_width, int i_height, bool i_buildable, bool i_walkable)
{
    new_tile = new Tile(this, row, col, i_width, i_height, i_buildable, i_walkable);
    return new_tile;

}

Entity *Board::create_entity(int x, int y, int height, int width)
{

    new_entity = new Entity(this, this);
    new_entity->m_x = x;
    new_entity->m_y = y;
    new_entity->m_width = width;
    new_entity->m_height = height;
    return new_entity;

}




Square *Board::find_square(int row, int col)
{
    Square* sq = qobject_cast<Square*>(db_tiles.value(getIndex(row, col)));
    if (sq) {
        return sq;
    } else {
        return 0;
    }
    return 0;
}
Entrance *Board::find_entrance(int row, int col)
{
    Entrance* sq = qobject_cast<Entrance*>(db_tiles.value(getIndex(row, col)));
    if (sq) {
        return sq;
    } else {
        return 0;
    }
    return 0;
}

Exit *Board::find_exit(int row, int col)
{
    Exit* sq = qobject_cast<Exit*>(db_tiles.value(getIndex(row, col)));
    if (sq) {
        return sq;
    } else {
        return 0;
    }
    return 0;
}

Wall *Board::find_wall(int row, int col)
{
    Wall* sq = qobject_cast<Wall*>(db_tiles.value(getIndex(row, col)));
    if (sq) {
        return sq;
    } else {
        return 0;
    }
    return 0;
}

Tile *Board::find_tile(int row, int col)
{
    Square* sq = find_square(row, col);
    if (sq)
        return sq->m_tile;

    Entrance* en = find_entrance(row, col);
    if (en)
        return en->m_tile;

    Exit* ex = find_exit(row, col);
    if (ex)
        return ex->m_tile;

    Wall* wa = find_wall(row,col);
    if (wa)
        return wa->m_tile;

    return 0;
}

Path *Board::find_path(int row, int col)
{
    int idx = getIndex(row, col);
    Path* path = db_paths.value(idx, 0);
    if (path) {
        return path;
    } else {

        new_path = new Path(this);
        this->db_paths.insert(getIndex(row, col), new_path);
        return new_path;

    }
    return 0;
}

QList<Tile *> Board::find_neighbors(Tile *i_tile)
{
    QList<Tile*> rv;

    int myRow = i_tile->m_row;
    int myCol = i_tile->m_col;

    QList<int> offsets;
    offsets << -1 << 0 << 1;
    foreach (int r, offsets)  {
        foreach (int c, offsets) {
            Tile* atile = find_tile(myRow + r, myCol + c);
            if (atile) {
                if (((c == 0) || (r == 0)) && (c != r)) {
                    if ((atile->m_walkable) && (!rv.contains(atile)) && (atile != i_tile)) { rv << atile; }
                }
            }
        }
    }
    return rv;
}

