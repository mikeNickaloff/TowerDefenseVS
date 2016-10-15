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
#include "gun.h"
#include "../src_common/astarpath.h"
#include <QtDebug>
#include <QTimer>
#include <QPointer>
#include <QVariant>
#include <QThread>
#include <QRect>
#include <QPoint>
Board::Board(QObject *parent, Game *i_game) : QObject(parent), m_game(i_game)
{
    numRows = 50;
    numColumns = 50;
    //populate_entry_paths();
    //QTimer::singleShot(10000, this, SLOT(populate_entry_paths()));

    entrance_index = 0;
    this->fireTimer = new QTimer(this);
    connect(fireTimer, SIGNAL(timeout()), this, SLOT(fire_all()));
    fireTimer->start(250);
    numWaves = 0;
    numEnemies = 0;
    wave_size = 4;
    waves_per_level = 2;
    new_star = new AStarPath(this, this);

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
    eraseTile(row,col);
    this->new_square = new Square(create_tile(row, col, tileWidth, tileHeight, false, true));
    db_tiles.insert(getIndex(row, col), new_square);
    //  qDebug() << "Board: Got word to create new Square" << new_square;
    emit this->signal_square_added(new_square);
    emit this->signal_pathing_set_walkable(row, col, true);
    new_square->m_tile->setBuildable(false);
    //  this->connect(new_square, SIGNAL(signal_place_gun(int,int,int)), this, SLOT(placeGun(int,int,int)));
    connect(new_square, SIGNAL(tileSelected(bool)), this, SLOT(unselect_all_but_sender(bool)));
    connect(new_square, SIGNAL(signal_show_gunStore(bool)), this, SLOT(show_gunStore(bool)));

}

void Board::placeEntrance(int row, int col) {
    this->new_entrance = new Entrance(create_tile(row, col, tileWidth, tileHeight, false, true));
    db_tiles.insert(getIndex(row, col), new_entrance);
    emit this->signal_entrance_added(new_entrance);
    emit this->signal_pathing_set_walkable(row, col, true);
    Path* path = find_path(row, col);
    path->clear_path();
}

void Board::placeExit(int row, int col) {
    this->new_exit = new Exit(create_tile(row, col, tileWidth, tileHeight, false, true));
    db_tiles.insert(getIndex(row, col), new_exit);
    emit this->signal_exit_added(new_exit);
    emit this->signal_pathing_set_walkable(row, col, true);
}

void Board::placeGun(int row, int col, int gun_type)
{
    eraseTile(row, col);
    this->new_gun = new Gun(create_tile(row, col, tileWidth, tileHeight, false, false));
    triggering_node = qMakePair(row, col);
    db_tiles.insert(getIndex(row, col), new_gun);
    new_gun->m_type = gun_type;
    connect(this, SIGNAL(signal_check_entity_within_range(QPoint,QPoint, Entity*)), new_gun, SLOT(check_entity_within_range(QPoint,QPoint,Entity*)));
    this->randomize_paths();
    foreach (Tile* ti, this->find_neighbors(new_gun->m_tile)) {

        if (ti->m_walkable) { ti->setBuildable(true); }
        foreach (Tile* pti, find_neighbors(ti)) {
            if (pti->m_walkable) {
                pti->setBuildable(true);
            }
            foreach (Tile* uti, find_neighbors(pti)) {
                if (uti->m_walkable) {
                    uti->setBuildable(true);
                }
            }
        }
    }


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
        new_path = new Path(this, this);
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
        Path* path = this->find_path(getRow(i.key()), getCol(i.key()));
        path->clear_path();
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
    placeGun(5, 5, 1);
    connect(m_paththread, SIGNAL(place_last_gun(bool)), this, SLOT(place_last_gun(bool)));
    //m_paththread->start();
    entrance_index = 0;
    exit_index = -1;
    randomize_paths();
    //next_exit();

    QTimer::singleShot(25000, this, SLOT(spawn_random_enemy()));

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
    new_path = new Path(this, this);
    new_path->m_nodes << this->db_paths.value(getIndex(i_tile->m_row, i_tile->m_col))->m_nodes;
    new_enemy->m_entity->m_path = new_path;
    new_enemy->m_entity->m_speed = speed;
    new_enemy->m_entity->m_entityIndex = lastEntity;
    //new_enemy->m_entity->next_path_tile();
    emit this->signal_enemy_added(new_enemy);
    QTimer::singleShot(speed, new_enemy->m_entity, SLOT(next_path_tile()));
}

void Board::spawn_random_enemy()
{
    entrance_index++;
    numEnemies++;
    if (entrance_index >= entrances.count()) { entrance_index = 0; }
    this->create_enemy(this->entrances.at(entrance_index)->m_tile, this->tileHeight, this->tileWidth, 1200, 335 * m_game->m_level, entrance_index != 0 ? entrance_index : 1);
    if (numEnemies < wave_size) {
        QTimer::singleShot(1100, this, SLOT(spawn_random_enemy()));
    } else {
        numWaves++;
        numEnemies = 0;
        if (numWaves < this->waves_per_level) {
            QTimer::singleShot(5000, this, SLOT(spawn_random_enemy()));
        } else {
            this->m_game->m_level++;
            emit m_game->levelChanged(m_game->m_level);
            this->numWaves = 0;
            QTimer::singleShot(12000, this, SLOT(spawn_random_enemy()));
        }
    }
}

void Board::eraseEntity(int entityIndex)
{
    emit this->signal_entity_erased(db_entities.value(entityIndex, 0));
    this->db_entities.remove(entityIndex);
}

void Board::randomize_paths()
{

    this->m_paththread->start();
    //  QTimer::singleShot(20000, this, SLOT(randomize_paths()));
}

void Board::place_last_gun(bool shouldPlace)
{


    if (shouldPlace == true) {
        if (new_gun)
            emit this->signal_gun_added(new_gun);
    } else {
        if (new_gun)
            placeSquare(new_gun->m_tile->m_row, new_gun->m_tile->m_col);
    }
    //eraseTile(getRow(last_tlist), getCol(last_tlist));
    //   placeSquare(getRow(last_tlist), getCol(last_tlist));
}

void Board::show_gunStore(bool is_shown)
{
    emit this->signal_show_gunStore(is_shown);

}

void Board::unselect_all_but_sender(bool is_selected)
{
    if (is_selected == true)  {
        Square* sq = qobject_cast<Square*>(sender());
        if (sq) {
            foreach (int idx, this->db_tiles.keys()) {
                Square* tmp_sq = find_square(getRow(idx), getCol(idx));
                if (tmp_sq) {
                    if (sq != tmp_sq) {
                        tmp_sq->setSelected(false);
                    }
                }
            }
        } else {
            foreach (int idx, this->db_tiles.keys()) {
                Square* tmp_sq = find_square(getRow(idx), getCol(idx));
                if (tmp_sq) {

                    tmp_sq->setSelected(false);

                }
            }
        }
    }

}

void Board::place_gun_on_selected(int gunType)
{
    foreach (int idx, this->db_tiles.keys()) {
        Square* tmp_sq = find_square(getRow(idx), getCol(idx));
        if (tmp_sq) {
            if (tmp_sq->m_selected) {
                this->placeGun(getRow(idx), getCol(idx), gunType);
            }

        }

    }
}

void Board::check_entity_within_range(QPoint oldPos, QPoint newPos)
{
    Entity* en = qobject_cast<Entity*>(sender());
    if (en) {
        emit this->signal_check_entity_within_range(oldPos, newPos, en);
    }
}

void Board::fire_all()
{
    QHash<int, QObject*>::const_iterator u = this->db_tiles.constBegin();
    while (u != db_tiles.constEnd()) {
        Gun* gu = this->find_gun(getRow(u.key()), getCol(u.key()));
        if (gu) {
            gu->fire();

        }


        u++;
    }
}

void Board::slot_shell_explode(int isplash_distance, int isplash_damage, int idamage, int ix, int iy)
{
    // qDebug() << "Exploding shell at " << ix << iy << "with damage" << idamage << "and splash damage/distance" << isplash_damage << isplash_distance;
    QHash<int, QObject*>::const_iterator u = this->db_entities.constBegin();
    while (u != db_entities.constEnd()) {
        Enemy* en = qobject_cast<Enemy*>(u.value());
        if (en) {
            QRect eRect(en->m_entity->realpos().x() - (0.5 * en->m_entity->m_width), en->m_entity->realpos().y() - (0.5 * en->m_entity->m_height), en->m_entity->m_width, en->m_entity->m_height);
            if (eRect.contains(QPoint(ix, iy), false)) {
                en->m_health -= idamage;
                en->m_health -= isplash_damage;
            } else {
                int distance_from_splash = QPoint(QPoint(ix, iy) - en->m_entity->realpos()).manhattanLength();
                if (distance_from_splash <= isplash_distance) {

                    en->m_health -= qRound((qreal)(distance_from_splash / isplash_distance) * isplash_damage);

                }
            }
            if (en->m_health <= 0) {
                if (en->m_entity->m_path->m_nodes.count() > 0) {
                    m_game->award_defenders(m_game->m_level * 2);
                    en->m_entity->m_path->clear_path();
                }
            }
        }

        u++;
    }
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
    this->connect(new_entity, SIGNAL(callout_position(QPoint,QPoint)), this, SLOT(check_entity_within_range(QPoint,QPoint)));
    this->connect(new_entity, SIGNAL(completed_path(int)), this, SLOT(eraseEntity(int)));
    this->connect(new_entity, SIGNAL(killed(int)), this, SLOT(eraseEntity(int)));

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

Gun *Board::find_gun(int row, int col)
{
    Gun* sq = qobject_cast<Gun*>(db_tiles.value(getIndex(row, col)));
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

    Gun* gu = find_gun(row, col);
    if (gu)
        return gu->m_tile;

    return 0;
}

Path *Board::find_path(int row, int col)
{
    int idx = getIndex(row, col);
    Path* path = db_paths.value(idx, 0);
    if (path) {
        return path;
    } else {

        new_path = new Path(this, this);
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
    offsets << 1 << 0 << -1;
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

