import QtQuick 2.7
import QtQuick.Window 2.2
import com.towerdefensevs 1.0
import "./src_qml/src_js/BackendLogic.js" as BackendLogic
import "./src_qml/src_js/FrontEndLogic.js" as FrontEndLogic

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property var m_squares: []
    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
        }
    }


    Component.onCompleted: {

        game.createBoard();



        // dynamic object creation
        game.board.signal_square_added.connect(BackendLogic.create_square);
        game.board.signal_entrance_added.connect(BackendLogic.create_entrance);
        game.board.signal_exit_added.connect(BackendLogic.create_exit);

        // create map
        game.createMap();

        // initialize grid
        FrontEndLogic.init_grid(game.board.numRows, game.board.numColumns);


        // pathing logic connections
        game.board.signal_pathing_set_walkable.connect(FrontEndLogic.set_grid_node_walkable);

        FrontEndLogic.init_grid(game.board.numRows, game.board.numColumns);

        game.board.signal_update_pathing_grid.connect(FrontEndLogic.init_grid);
       game.board.signal_get_shortest_path.connect(FrontEndLogic.get_shortest_path);
       game.board.signal_get_shortest_target_path.connect(FrontEndLogic.get_shortest_path);

        game.board.update_walkable_states();






     //   FrontEndLogic.get_shortest_path(0,0, 10, 10);
        //create paths
        game.board.populate_entry_paths();


    }
   Rectangle {
       id: background
       anchors.fill: parent
       z: 0
   }
    TextEdit {
        id: textEdit
        text: qsTr("Enter some text...")
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 1
        }
    }
}
