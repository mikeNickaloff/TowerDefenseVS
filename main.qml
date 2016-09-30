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

        // pathing logic connections
        FrontEndLogic.init_grid();
        game.board.signal_pathing_set_walkable.connect(FrontEndLogic.set_grid_node_walkable);
        game.board.signal_get_shortest_path.connect(FrontEndLogic.get_shortest_path);

        // create map
        game.createMap();


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
