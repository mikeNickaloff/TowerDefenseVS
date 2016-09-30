Qt.include("core/Grid.js");
Qt.include("finders/AStarFinder.js");

 var grid;
function init_grid(rowCount, colCount) {
	grid = new Grid(colCount, rowCount);
	
} 
function set_grid_node_walkable(row, col, is_walkable) {
	grid.setWalkableAt(col, row, is_walkable);
}
function get_shortest_path(row_1, col_1, row_2, col_2, targetObject) {

   


    var finder = new AStarFinder({ allowDiagonal: false, dontCrossCorners: true });
    var p1_walkable = grid.isWalkableAt(col_1, row_1);
	var p2_walkable = grid.isWalkableAt(col_2, row_2);
   
    grid.setWalkableAt(col_1, row_1, true);
    grid.setWalkableAt(col_2, row_2, true);
    var rv = finder.findPath(col_1, row_1, col_2, row_2, grid);
	
	grid.setWalkableAt(col_1, row_1, p1_walkable);
    grid.setWalkableAt(col_2, row_2, p2_walkable);
	
	  if (rv[2] != null) {
		  if (targetObject == null) { 
			game.board.clear_path_data();
			var q = 0;
            while (rv[q] != null) {
               game.board.add_path_data(parseInt(rv[q][0]),parseInt(rv[q][1]));
               q++;
        
           }
		  } else {
			  
			  game.board.clear_target_path_data(targetObject);
			var q = 0;
            while (rv[q] != null) {
               game.board.add_target_path_data(targetObject, parseInt(rv[q][0]),parseInt(rv[q][1]));
               q++;
        
           }  
			  
		  }
                                

                                
      }
	
    
}
