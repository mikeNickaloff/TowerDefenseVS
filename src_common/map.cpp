#include "map.h"
#include "../src_game/square.h"
#include "../src_game/wall.h"
#include "../src_game/entrance.h"
#include "../src_game/exit.h"


Map::Map(QObject *parent) : QObject(parent)
{

}
void Map::create_blank_map() {
    this->rowCount = 15;
    this->colCount = 25;
    emit this->Map::rowCountChanged(rowCount);
    emit this->Map::colCountChanged(colCount);
    emit this->Map::tileHeightChanged(30);
    emit this->Map::tileWidthChanged(30);
    for (int i=0; i<rowCount; i++) {
        for (int j=0; j<colCount; j++) {
            bool placed = false;
            if ((i == 0) || (j == 0) || (i == (rowCount - 1)) || (j == (colCount - 1))) {

                if ((i == 0) && ((j % 5) == 1)) { emit this->placeEntrance(i,j); placed = true; }
                if (((i == 0) && (((j % 5) != 1) || ((j % 5) == 2))) || (j == 0) || (j == (colCount - 1)) || ((i == (rowCount - 1)) && (j != (rowCount * 0.5)))) { emit this->placeWall(i,j); placed = true; }

                if ((i == (rowCount - 1)) && (j == qRound(rowCount * 0.5))) { emit this->placeExit(i,j); placed = true; }
               /* if (!placed) {
                   emit this->placeWall(i,j);
               } */
            }
            if (((i % 3) == 2) && ((j % 4) == 3)) {
                emit this->placeWall(i, j); placed = true;
            }
                    //else {
             //if (((i + j) % j) > 6) { emit this->placeWall(i, j); placed = true; }
            //}

            if (!placed) {
                emit this->placeSquare(i,j);
            }
        }
    }

}
