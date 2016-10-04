#include "map.h"
#include "../src_game/square.h"
#include "../src_game/wall.h"
#include "../src_game/entrance.h"
#include "../src_game/exit.h"


Map::Map(QObject *parent) : QObject(parent)
{

}
void Map::create_blank_map() {
    this->rowCount = 10;
    this->colCount = 20;
    emit this->Map::rowCountChanged(rowCount);
    emit this->Map::colCountChanged(colCount);
    emit this->Map::tileHeightChanged(50);
    emit this->Map::tileWidthChanged(50);
    for (int i=0; i<rowCount; i++) {
        for (int j=0; j<colCount; j++) {
            bool placed = false;
            if ((i == 0) || (j == 0) || (i == (rowCount - 1)) || (j == (colCount - 1))) {

                if ((i == 0) && ((j % 8) == 1)) { emit this->placeEntrance(i,j); placed = true; }
                if (((i == 0) && (((j % 8) != 1) || ((j % 8) == 2))) || (j == 0) || (j == (colCount - 1)) || ((i == (rowCount - 1)) && (j != (rowCount * 0.5)))) { emit this->placeWall(i,j); placed = true; }

                if ((i == (rowCount - 1)) && (j == qRound(rowCount * 0.5))) { emit this->placeExit(i,j); placed = true; }

               /* if (!placed) {
                   emit this->placeWall(i,j);
               } */
            }
            if ((!placed) && ((((j * colCount ) + i) % 17) == 0)) { emit this->placeWall(i, j); placed = true; }
        //    if (((i % 3) == 2) && ((j % 4) == 3)) {
        //        emit this->placeWall(i, j); placed = true;
        //    }
                    //else {
             //if (((i + j) % j) > 6) { emit this->placeWall(i, j); placed = true; }
            //}

            if (!placed) {
                emit this->placeSquare(i,j);
            }
        }
    }

}
