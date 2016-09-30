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
#include "../src_common/game.h"
#include <QtDebug>
#include <QTimer>
#include <QPointer>
#include <QVariant>
Board::Board(QObject *parent, Game *i_game) : QObject(parent), m_game(i_game)
{

}
void Board::changeRowCount(int newCount) {
numRows = newCount;
}
void Board::changeColCount(int newCount) {
numColumns = newCount;
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

void Board::clear_path_data()
{

}

void Board::clear_target_path_data(Enemy *targetObject)
{

}

void Board::add_path_data(int c1, int r1)
{

}

void Board::add_target_path_data(Enemy *targetObject, int c1, int r1)
{

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

