
var tiles = [];
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
