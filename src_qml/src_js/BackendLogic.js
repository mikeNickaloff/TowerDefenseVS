
var tiles = [];
var entities = [];
function create_square(new_square) {
   // console.log("BackendLogicJS: Got word to make new square: " + new_square);
    var component = Qt.createComponent("qrc:///src_qml/src_game/Square.qml");
    var sq = component.createObject(background, { "backend" : new_square });
    sq.x = new_square.tile.x
    sq.y = new_square.tile.y
    sq.width = new_square.tile.width;
    sq.height = new_square.tile.height;
    tiles[game.board.getIndex(new_square.tile.row, new_square.tile.col)] = sq;
    sq.visible = true;

    game.board.signal_tile_erased.connect(sq.check_if_erased);
    sq.i_have_been_erased.connect(sq.destroy);
    new_square.tileSelected.connect(sq.set_selected);

}
function change_tile_property(prop, val, row, col) {
    var obj = tiles[game.board.getIndex(row, col)];
    if (obj != null) {

       if (prop == "width") {
           obj.width = val;
       }
    }
}
function create_entrance(new_entrance) {
    var component = Qt.createComponent("qrc:///src_qml/src_game/Entrance.qml");
    var sq = component.createObject(background, { "backend" : new_entrance });
    sq.x = new_entrance.tile.x
    sq.y = new_entrance.tile.y
    sq.width = new_entrance.tile.width;
    sq.height = new_entrance.tile.height;
    tiles[game.board.getIndex(new_entrance.tile.row, new_entrance.tile.col)] = sq;
    sq.visible = true;

    game.board.signal_tile_erased.connect(sq.check_if_erased);
    sq.i_have_been_erased.connect(sq.destroy);
}


function create_exit(new_exit) {
    var component = Qt.createComponent("qrc:///src_qml/src_game/Exit.qml");
    var sq = component.createObject(background, { "backend" : new_exit });
    sq.x = new_exit.tile.x
    sq.y = new_exit.tile.y
    sq.width = new_exit.tile.width;
    sq.height = new_exit.tile.height;
    tiles[game.board.getIndex(new_exit.tile.row, new_exit.tile.col)] = sq;
    sq.visible = true;

    game.board.signal_tile_erased.connect(sq.check_if_erased);
    sq.i_have_been_erased.connect(sq.destroy);
}
function create_wall(new_wall) {
    var component = Qt.createComponent("qrc:///src_qml/src_game/Wall.qml");
    var sq = component.createObject(background, { "backend" : new_wall });
    sq.x = new_wall.tile.x
    sq.y = new_wall.tile.y
    sq.width = new_wall.tile.width;
    sq.height = new_wall.tile.height;
    tiles[game.board.getIndex(new_wall.tile.row, new_wall.tile.col)] = sq;
    sq.visible = true;

    game.board.signal_tile_erased.connect(sq.check_if_erased);
    sq.i_have_been_erased.connect(sq.destroy);
}

function create_enemy(new_enemy) {
    var component = Qt.createComponent("qrc:///src_qml/src_game/Enemy.qml");
    var sq = component.createObject(background, { "backend" : new_enemy, "x" : new_enemy.entity.x });
    sq.x = new_enemy.entity.x
    sq.y = new_enemy.entity.y
    sq.width = new_enemy.entity.width;
    sq.height = new_enemy.entity.height;
    entities.push(sq);
    sq.visible = true;

    game.board.signal_entity_erased.connect(sq.check_if_erased);
    sq.i_have_been_erased.connect(sq.destroy);
}

function create_gun(new_gun) {
    if (new_gun != null) {
    var component = Qt.createComponent("qrc:///src_qml/src_game/Gun.qml");
    var sq = component.createObject(background, { "backend" : new_gun, "gun_type" : new_gun.type });
    sq.x = new_gun.tile.x;
    sq.y = new_gun.tile.y;
        sq.opacity = 1.0;
    sq.width = new_gun.tile.width;
    sq.height = new_gun.tile.height;
    tiles[game.board.getIndex(new_gun.tile.row, new_gun.tile.col)] = sq;
    sq.visible = true;

    game.board.signal_tile_erased.connect(sq.check_if_erased);
    sq.i_have_been_erased.connect(sq.destroy);
    }
}
