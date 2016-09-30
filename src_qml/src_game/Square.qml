import QtQuick 2.0
import com.towerdefensevs 1.0

Rectangle {
    id: rect
    property Square backend

    color: "red"
    border.color: "black"
    border.width: 1
    z: 100
    function changeWidth(new_width) {
        rect.width = new_width;
    }
    Behavior on width {

        NumberAnimation {
            duration: (20 * backend.tile.col) + (20 * backend.tile.row)

        }
    }
    Component.onCompleted: {
        if (backend !== null) {
            backend.tile.myWidthChanged.connect(changeWidth);


        }
    }
    signal i_have_been_erased();
    function check_if_erased(row, col) {
        if (backend != null) {
            if ((backend.tile.row === row) && (backend.tile.col === col)) {

                i_have_been_erased();
            }
        }
    }


    MouseArea {
        anchors.fill: parent
        width: parent.width
        height: parent.height
        onClicked: {
            console.log("Got clicked");
            backend.gotMouseClick();
        }
        z: 101
    }
}
