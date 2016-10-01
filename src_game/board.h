#ifndef BOARD_H
#define BOARD_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QHash>
#include <QVariant>

class Enemy;
class Entity;
class Entrance;
class Exit;
class Projectile;
class Square;
class Tile;
class Tower;
class Wall;
class Game;
class Path;
class Board : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int numColumns MEMBER numColumns)
    Q_PROPERTY(int numRows MEMBER numRows)
public:
    explicit Board(QObject *parent = 0, Game* i_game = 0);
    Game* m_game;

    int numColumns;
    int numRows;
    int tileHeight;
    int tileWidth;


    Tile* new_tile;
    Wall* new_wall;
    Square* new_square;
    Entrance* new_entrance;
    Exit* new_exit;

    QHash<int, QObject*> db_entities;


    QHash<int, QObject*> db_tiles;

    QHash<int, Path*> db_paths;


    QList<Exit*> exits;
    QList<Entrance*> entrances;

    int entrance_index;
    int exit_index;

    Q_INVOKABLE int getIndex(int row, int col);
    Q_INVOKABLE int getRow(int index);
    Q_INVOKABLE int getCol(int index);

    Q_INVOKABLE Tile* create_tile(int row, int col, int i_width, int i_height, bool i_buildable, bool i_walkable);
    Q_INVOKABLE Square* find_square(int row, int col);
    Q_INVOKABLE Entrance* find_entrance(int row, int col);
    Q_INVOKABLE Exit* find_exit(int row, int col);
    Q_INVOKABLE Wall* find_wall(int row, int col);
    int anim_tile_removal_row;
    int anim_tile_removal_col;
    Q_INVOKABLE Tile* find_tile(int row, int col);
    Q_INVOKABLE Path* find_path(int row, int col);
signals:
    void signal_wall_added(Wall* wall_obj);
    void signal_square_added(Square* square_obj);
    void signal_entrance_added(Entrance* square_obj);
     void signal_exit_added(Exit* square_obj);
     void signal_tile_erased(int row, int col);

     void signal_pathing_set_walkable(int row, int col, bool isWalkable);
     void signal_get_shortest_target_path(int c1, int r1, int c2, int r2, Enemy* targetObject);
       void signal_get_shortest_path(int c1, int r1, int c2, int r2);
     void signal_update_pathing_grid(int rowCount, int colCount);
public slots:
    void changeRowCount(int newCount);
    void changeColCount(int newCount);
    void eraseTile(int row, int col);

    void tileHeightChanged(int newHeight);
    void tileWidthChanged(int newWidth);
    // slots for assigning special map squares that player cannot
    // change during a game

    void placeWall(int row, int col);
    void placeSquare(int row, int col);
    void placeEntrance(int row, int col);
    void placeExit(int row, int col);


    void clear_path_data(int from_row, int from_col);
    void clear_target_path_data(Enemy* targetObject);
    void add_path_data(int c1, int r1, int from_row, int from_col);
    void add_target_path_data(Enemy* targetObject, int c1, int r1);
    void update_walkable_states();

    void populate_entry_paths();

    void next_exit();
    void next_entrance();

};

#endif // BOARD_H
