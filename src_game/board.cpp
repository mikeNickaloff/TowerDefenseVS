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
    anim_tile_removal_col = 0;
    anim_tile_removal_row = 0;
    QTimer::singleShot(30, this, SLOT(animate_tile_removal()));
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
}

void Board::placeSquare(int row, int col) {
    this->new_square = new Square(create_tile(row, col, tileWidth, tileHeight, true, true));
    db_tiles.insert(getIndex(row, col), new_square);
  //  qDebug() << "Board: Got word to create new Square" << new_square;
    emit this->signal_square_added(new_square);


}

void Board::placeEntrance(int row, int col) {
    this->new_entrance = new Entrance(create_tile(row, col, tileWidth, tileHeight, false, true));
    db_tiles.insert(getIndex(row, col), new_entrance);
    emit this->signal_entrance_added(new_entrance);
}

void Board::placeExit(int row, int col) {
    this->new_exit = new Exit(create_tile(row, col, tileWidth, tileHeight, false, true));
    db_tiles.insert(getIndex(row, col), new_exit);
    emit this->signal_exit_added(new_exit);
}



void Board::animate_tile_removal()
{
    int row = anim_tile_removal_row;
    int col = anim_tile_removal_col;
    int interval = 80;

    Square* sq = find_square(row, col);
    if (sq) { sq->m_tile->setMyWidth((int) (this->tileWidth)); }

    sq = find_square(col, row);
    if (sq) { sq->m_tile->setMyWidth((int) (this->tileWidth)); }

    sq = find_square(qAbs(col - row), qAbs(row - col));
    if (sq) { sq->m_tile->setMyWidth((int) (this->tileWidth * (1))); }
    sq = find_square(qAbs(row - col), qAbs(col - row));
    if (sq) { sq->m_tile->setMyWidth((int) (this->tileWidth * (1))); }
    for (int i=5; i<14; i++) {
        sq = find_square(qAbs(row - i), qAbs(col - i));
        if (sq) { sq->m_tile->setMyWidth((int) (this->tileWidth * (1))); }
    }

    row++;
    if (row > this->numRows) { row = 0; col++; interval = 125; }
    if (col > this->numColumns) {
        row = 0;
        col = 0;
        interval = 2000;

    } else {



    }


    sq = find_square(row, col);
    if (sq) { sq->m_tile->setMyWidth((int) (this->tileWidth * (0.25))); }
    sq = find_square(col, row);
    if (sq) { sq->m_tile->setMyWidth((int) (this->tileWidth * (0.25))); }
    sq = find_square(qAbs(col - row), qAbs(row - col));
    if (sq) { sq->m_tile->setMyWidth((int) (this->tileWidth * (0.25))); }
    sq = find_square(qAbs(row - col), qAbs(col - row));
    if (sq) { sq->m_tile->setMyWidth((int) (this->tileWidth * (0.25))); }
    for (int i=5; i<14; i += 2) {
        sq = find_square(qAbs(row - i), qAbs(col - i));
        if (sq) { sq->m_tile->setMyWidth((int) (this->tileWidth * (0.15))); }
    }
    anim_tile_removal_col = col;
    anim_tile_removal_row = row;
    QTimer::singleShot(interval, this, SLOT(animate_tile_removal()));
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

